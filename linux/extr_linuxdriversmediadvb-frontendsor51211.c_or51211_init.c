#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct or51211_state {int initialized; struct or51211_config* config; } ;
struct or51211_config {int (* request_firmware ) (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  demod_address; } ;
struct firmware {int dummy; } ;
struct dvb_frontend {struct or51211_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  OR51211_DEFAULT_FIRMWARE ; 
 unsigned char* cmd_buf ; 
 int /*<<< orphan*/  dprintk (char*,unsigned char*) ; 
 scalar_t__ i2c_readbytes (struct or51211_state*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ i2c_writebytes (struct or51211_state*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int or51211_load_firmware (struct dvb_frontend*,struct firmware const*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int stub1 (struct dvb_frontend*,struct firmware const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int or51211_init(struct dvb_frontend* fe)
{
	struct or51211_state* state = fe->demodulator_priv;
	const struct or51211_config* config = state->config;
	const struct firmware* fw;
	unsigned char get_ver_buf[] = {0x04,0x00,0x30,0x00,0x00};
	unsigned char rec_buf[14];
	int ret,i;

	if (!state->initialized) {
		/* Request the firmware, this will block until it uploads */
		pr_info("Waiting for firmware upload (%s)...\n",
			OR51211_DEFAULT_FIRMWARE);
		ret = config->request_firmware(fe, &fw,
					       OR51211_DEFAULT_FIRMWARE);
		pr_info("Got Hotplug firmware\n");
		if (ret) {
			pr_warn("No firmware uploaded (timeout or file not found?)\n");
			return ret;
		}

		ret = or51211_load_firmware(fe, fw);
		release_firmware(fw);
		if (ret) {
			pr_warn("Writing firmware to device failed!\n");
			return ret;
		}
		pr_info("Firmware upload complete.\n");

		/* Set operation mode in Receiver 1 register;
		 * type 1:
		 * data 0x50h  Automatic sets receiver channel conditions
		 *             Automatic NTSC rejection filter
		 *             Enable  MPEG serial data output
		 *             MPEG2tr
		 *             High tuner phase noise
		 *             normal +/-150kHz Carrier acquisition range
		 */
		if (i2c_writebytes(state,state->config->demod_address,
				   cmd_buf,3)) {
			pr_warn("Load DVR Error 5\n");
			return -1;
		}

		/* Read back ucode version to besure we loaded correctly */
		/* and are really up and running */
		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x03;
		rec_buf[3] = 0x00;
		msleep(30);
		if (i2c_writebytes(state,state->config->demod_address,
				   rec_buf,3)) {
			pr_warn("Load DVR Error A\n");
			return -1;
		}
		msleep(3);
		if (i2c_readbytes(state,state->config->demod_address,
				  &rec_buf[10],2)) {
			pr_warn("Load DVR Error B\n");
			return -1;
		}

		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x01;
		rec_buf[3] = 0x00;
		msleep(20);
		if (i2c_writebytes(state,state->config->demod_address,
				   rec_buf,3)) {
			pr_warn("Load DVR Error C\n");
			return -1;
		}
		msleep(3);
		if (i2c_readbytes(state,state->config->demod_address,
				  &rec_buf[12],2)) {
			pr_warn("Load DVR Error D\n");
			return -1;
		}

		for (i = 0; i < 8; i++)
			rec_buf[i]=0xed;

		for (i = 0; i < 5; i++) {
			msleep(30);
			get_ver_buf[4] = i+1;
			if (i2c_writebytes(state,state->config->demod_address,
					   get_ver_buf,5)) {
				pr_warn("Load DVR Error 6 - %d\n", i);
				return -1;
			}
			msleep(3);

			if (i2c_readbytes(state,state->config->demod_address,
					  &rec_buf[i*2],2)) {
				pr_warn("Load DVR Error 7 - %d\n", i);
				return -1;
			}
			/* If we didn't receive the right index, try again */
			if ((int)rec_buf[i*2+1]!=i+1){
			  i--;
			}
		}
		dprintk("read_fwbits %10ph\n", rec_buf);

		pr_info("ver TU%02x%02x%02x VSB mode %02x Status %02x\n",
			rec_buf[2], rec_buf[4], rec_buf[6], rec_buf[12],
			rec_buf[10]);

		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x03;
		rec_buf[3] = 0x00;
		msleep(20);
		if (i2c_writebytes(state,state->config->demod_address,
				   rec_buf,3)) {
			pr_warn("Load DVR Error 8\n");
			return -1;
		}
		msleep(20);
		if (i2c_readbytes(state,state->config->demod_address,
				  &rec_buf[8],2)) {
			pr_warn("Load DVR Error 9\n");
			return -1;
		}
		state->initialized = 1;
	}

	return 0;
}