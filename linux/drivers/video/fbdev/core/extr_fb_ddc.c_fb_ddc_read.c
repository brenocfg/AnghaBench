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
struct i2c_algo_bit_data {int /*<<< orphan*/  data; int /*<<< orphan*/  (* setscl ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* setsda ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  udelay; scalar_t__ (* getscl ) (int /*<<< orphan*/ ) ;} ;
struct i2c_adapter {int /*<<< orphan*/  class; struct i2c_algo_bit_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 unsigned char* fb_do_probe_ddc_edid (struct i2c_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

unsigned char *fb_ddc_read(struct i2c_adapter *adapter)
{
	struct i2c_algo_bit_data *algo_data = adapter->algo_data;
	unsigned char *edid = NULL;
	int i, j;

	algo_data->setscl(algo_data->data, 1);

	for (i = 0; i < 3; i++) {
		/* For some old monitors we need the
		 * following process to initialize/stop DDC
		 */
		algo_data->setsda(algo_data->data, 1);
		msleep(13);

		algo_data->setscl(algo_data->data, 1);
		if (algo_data->getscl) {
			for (j = 0; j < 5; j++) {
				msleep(10);
				if (algo_data->getscl(algo_data->data))
					break;
			}
			if (j == 5)
				continue;
		} else {
			udelay(algo_data->udelay);
		}

		algo_data->setsda(algo_data->data, 0);
		msleep(15);
		algo_data->setscl(algo_data->data, 0);
		msleep(15);
		algo_data->setsda(algo_data->data, 1);
		msleep(15);

		/* Do the real work */
		edid = fb_do_probe_ddc_edid(adapter);
		algo_data->setsda(algo_data->data, 0);
		algo_data->setscl(algo_data->data, 0);
		msleep(15);

		algo_data->setscl(algo_data->data, 1);
		if (algo_data->getscl) {
			for (j = 0; j < 10; j++) {
				msleep(10);
				if (algo_data->getscl(algo_data->data))
					break;
			}
		} else {
			udelay(algo_data->udelay);
		}

		algo_data->setsda(algo_data->data, 1);
		msleep(15);
		algo_data->setscl(algo_data->data, 0);
		algo_data->setsda(algo_data->data, 0);
		if (edid)
			break;
	}
	/* Release the DDC lines when done or the Apple Cinema HD display
	 * will switch off
	 */
	algo_data->setsda(algo_data->data, 1);
	algo_data->setscl(algo_data->data, 1);

	adapter->class |= I2C_CLASS_DDC;
	return edid;
}