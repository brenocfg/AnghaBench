#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct vp702x_fe_state {scalar_t__ voltage; int status_check_interval; TYPE_1__* d; int /*<<< orphan*/  next_status_check; } ;
struct vp702x_device_state {int* buf; int /*<<< orphan*/  buf_mutex; } ;
struct dtv_frontend_properties {int frequency; int symbol_rate; } ;
struct dvb_frontend {struct vp702x_fe_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_2__ {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 scalar_t__ SEC_VOLTAGE_18 ; 
 int /*<<< orphan*/  deb_fe (char*,...) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vp702x_chksum (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vp702x_usb_inout_op (TYPE_1__*,int*,int,int*,int,int) ; 

__attribute__((used)) static int vp702x_fe_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *fep = &fe->dtv_property_cache;
	struct vp702x_fe_state *st = fe->demodulator_priv;
	struct vp702x_device_state *dst = st->d->priv;
	u32 freq = fep->frequency/1000;
	/*CalFrequency*/
/*	u16 frequencyRef[16] = { 2, 4, 8, 16, 32, 64, 128, 256, 24, 5, 10, 20, 40, 80, 160, 320 }; */
	u64 sr;
	u8 *cmd;

	mutex_lock(&dst->buf_mutex);

	cmd = dst->buf;
	memset(cmd, 0, 10);

	cmd[0] = (freq >> 8) & 0x7f;
	cmd[1] =  freq       & 0xff;
	cmd[2] = 1; /* divrate == 4 -> frequencyRef[1] -> 1 here */

	sr = (u64) (fep->symbol_rate/1000) << 20;
	do_div(sr,88000);
	cmd[3] = (sr >> 12) & 0xff;
	cmd[4] = (sr >> 4)  & 0xff;
	cmd[5] = (sr << 4)  & 0xf0;

	deb_fe("setting frontend to: %u -> %u (%x) LNB-based GHz, symbolrate: %d -> %lu (%lx)\n",
			fep->frequency, freq, freq, fep->symbol_rate,
			(unsigned long) sr, (unsigned long) sr);

/*	if (fep->inversion == INVERSION_ON)
		cmd[6] |= 0x80; */

	if (st->voltage == SEC_VOLTAGE_18)
		cmd[6] |= 0x40;

/*	if (fep->symbol_rate > 8000000)
		cmd[6] |= 0x20;

	if (fep->frequency < 1531000)
		cmd[6] |= 0x04;

	if (st->tone_mode == SEC_TONE_ON)
		cmd[6] |= 0x01;*/

	cmd[7] = vp702x_chksum(cmd,0,7);

	st->status_check_interval = 250;
	st->next_status_check = jiffies;

	vp702x_usb_inout_op(st->d, cmd, 8, cmd, 10, 100);

	if (cmd[2] == 0 && cmd[3] == 0)
		deb_fe("tuning failed.\n");
	else
		deb_fe("tuning succeeded.\n");

	mutex_unlock(&dst->buf_mutex);

	return 0;
}