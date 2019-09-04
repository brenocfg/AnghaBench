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
struct pxa_i2c {int dummy; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  dev; struct pxa_i2c* algo_data; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int I2C_RETRY ; 
 int ICR_IUE ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ i2c_debug ; 
 int i2c_pxa_do_pio_xfer (struct pxa_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_pxa_reset (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_scream_blue_murder (struct pxa_i2c*,char*) ; 
 int /*<<< orphan*/  i2c_pxa_set_slave (struct pxa_i2c*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i2c_pxa_pio_xfer(struct i2c_adapter *adap,
			    struct i2c_msg msgs[], int num)
{
	struct pxa_i2c *i2c = adap->algo_data;
	int ret, i;

	/* If the I2C controller is disabled we need to reset it
	  (probably due to a suspend/resume destroying state). We do
	  this here as we can then avoid worrying about resuming the
	  controller before its users. */
	if (!(readl(_ICR(i2c)) & ICR_IUE))
		i2c_pxa_reset(i2c);

	for (i = adap->retries; i >= 0; i--) {
		ret = i2c_pxa_do_pio_xfer(i2c, msgs, num);
		if (ret != I2C_RETRY)
			goto out;

		if (i2c_debug)
			dev_dbg(&adap->dev, "Retrying transmission\n");
		udelay(100);
	}
	i2c_pxa_scream_blue_murder(i2c, "exhausted retries");
	ret = -EREMOTEIO;
 out:
	i2c_pxa_set_slave(i2c, ret);
	return ret;
}