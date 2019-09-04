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
struct i2c_msg {int flags; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  nr; int /*<<< orphan*/  dev; struct cami2c* algo_data; } ;
struct cami2c {int status; int /*<<< orphan*/  flags; struct i2c_msg* msg; int /*<<< orphan*/  xfer_done; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2CFIER ; 
 int /*<<< orphan*/  I2CMCR ; 
 int /*<<< orphan*/  I2CMIER ; 
 int /*<<< orphan*/  I2CMSR ; 
 int /*<<< orphan*/  I2CSAR ; 
 int /*<<< orphan*/  I2CSCR ; 
 int /*<<< orphan*/  I2CSSR ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IDF_STOP ; 
 int IDS_ARBLOST ; 
 int IDS_NACK ; 
 int /*<<< orphan*/  OUT32 (struct cami2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ sh7760_i2c_busy_check (struct cami2c*) ; 
 int /*<<< orphan*/  sh7760_i2c_mrecv (struct cami2c*) ; 
 int /*<<< orphan*/  sh7760_i2c_msend (struct cami2c*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh7760_i2c_master_xfer(struct i2c_adapter *adap,
				  struct i2c_msg *msgs,
				  int num)
{
	struct cami2c *id = adap->algo_data;
	int i, retr;

	if (sh7760_i2c_busy_check(id)) {
		dev_err(&adap->dev, "sh7760-i2c%d: bus busy!\n", adap->nr);
		return -EBUSY;
	}

	i = 0;
	while (i < num) {
		retr = adap->retries;
retry:
		id->flags = ((i == (num-1)) ? IDF_STOP : 0);
		id->status = 0;
		id->msg = msgs;
		init_completion(&id->xfer_done);

		if (msgs->flags & I2C_M_RD)
			sh7760_i2c_mrecv(id);
		else
			sh7760_i2c_msend(id);

		wait_for_completion(&id->xfer_done);

		if (id->status == 0) {
			num = -EIO;
			break;
		}

		if (id->status & IDS_NACK) {
			/* wait a bit or i2c module stops working */
			mdelay(1);
			num = -EREMOTEIO;
			break;
		}

		if (id->status & IDS_ARBLOST) {
			if (retr--) {
				mdelay(2);
				goto retry;
			}
			num = -EREMOTEIO;
			break;
		}

		msgs++;
		i++;
	}

	id->msg = NULL;
	id->flags = 0;
	id->status = 0;

	OUT32(id, I2CMCR, 0);
	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMIER, 0);
	OUT32(id, I2CFIER, 0);

	/* reset slave module registers too: master mode enables slave
	 * module for receive ops (ack, data). Without this reset,
	 * eternal bus activity might be reported after NACK / ARBLOST.
	 */
	OUT32(id, I2CSCR, 0);
	OUT32(id, I2CSAR, 0);
	OUT32(id, I2CSSR, 0);

	return num;
}