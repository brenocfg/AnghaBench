#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cpu_addr; } ;
struct saa7146_dev {scalar_t__ revision; int /*<<< orphan*/  i2c_lock; TYPE_2__* ext; TYPE_1__ d_i2c; } ;
struct i2c_msg {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_I2C (char*,...) ; 
 int EIO ; 
 int EREMOTEIO ; 
 int ERESTARTSYS ; 
 int SAA7146_I2C_SHORT_DELAY ; 
 int SAA7146_USE_I2C_IRQ ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ saa7146_i2c_msg_cleanup (struct i2c_msg const*,int,int /*<<< orphan*/ *) ; 
 int saa7146_i2c_msg_prepare (struct i2c_msg const*,int,int /*<<< orphan*/ *) ; 
 int saa7146_i2c_reset (struct saa7146_dev*) ; 
 scalar_t__ saa7146_i2c_writeout (struct saa7146_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int saa7146_i2c_transfer(struct saa7146_dev *dev, const struct i2c_msg *msgs, int num, int retries)
{
	int i = 0, count = 0;
	__le32 *buffer = dev->d_i2c.cpu_addr;
	int err = 0;
	int short_delay = 0;

	if (mutex_lock_interruptible(&dev->i2c_lock))
		return -ERESTARTSYS;

	for(i=0;i<num;i++) {
		DEB_I2C("msg:%d/%d\n", i+1, num);
	}

	/* prepare the message(s), get number of u32s to transfer */
	count = saa7146_i2c_msg_prepare(msgs, num, buffer);
	if ( 0 > count ) {
		err = -EIO;
		goto out;
	}

	if ( count > 3 || 0 != (SAA7146_I2C_SHORT_DELAY & dev->ext->flags) )
		short_delay = 1;

	do {
		/* reset the i2c-device if necessary */
		err = saa7146_i2c_reset(dev);
		if ( 0 > err ) {
			DEB_I2C("could not reset i2c-device\n");
			goto out;
		}

		/* write out the u32s one after another */
		for(i = 0; i < count; i++) {
			err = saa7146_i2c_writeout(dev, &buffer[i], short_delay);
			if ( 0 != err) {
				/* this one is unsatisfying: some i2c slaves on some
				   dvb cards don't acknowledge correctly, so the saa7146
				   thinks that an address error occurred. in that case, the
				   transaction should be retrying, even if an address error
				   occurred. analog saa7146 based cards extensively rely on
				   i2c address probing, however, and address errors indicate that a
				   device is really *not* there. retrying in that case
				   increases the time the device needs to probe greatly, so
				   it should be avoided. So we bail out in irq mode after an
				   address error and trust the saa7146 address error detection. */
				if (-EREMOTEIO == err && 0 != (SAA7146_USE_I2C_IRQ & dev->ext->flags))
					goto out;
				DEB_I2C("error while sending message(s). starting again\n");
				break;
			}
		}
		if( 0 == err ) {
			err = num;
			break;
		}

		/* delay a bit before retrying */
		msleep(10);

	} while (err != num && retries--);

	/* quit if any error occurred */
	if (err != num)
		goto out;

	/* if any things had to be read, get the results */
	if ( 0 != saa7146_i2c_msg_cleanup(msgs, num, buffer)) {
		DEB_I2C("could not cleanup i2c-message\n");
		err = -EIO;
		goto out;
	}

	/* return the number of delivered messages */
	DEB_I2C("transmission successful. (msg:%d)\n", err);
out:
	/* another bug in revision 0: the i2c-registers get uploaded randomly by other
	   uploads, so we better clear them out before continuing */
	if( 0 == dev->revision ) {
		__le32 zero = 0;
		saa7146_i2c_reset(dev);
		if( 0 != saa7146_i2c_writeout(dev, &zero, short_delay)) {
			pr_info("revision 0 error. this should never happen\n");
		}
	}

	mutex_unlock(&dev->i2c_lock);
	return err;
}