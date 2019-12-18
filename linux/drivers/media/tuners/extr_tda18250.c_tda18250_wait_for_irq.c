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
typedef  unsigned int u8 ;
struct tda18250_dev {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* tuner_priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R08_IRQ1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int,char*) ; 
 struct tda18250_dev* i2c_get_clientdata (struct i2c_client*) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int tda18250_wait_for_irq(struct dvb_frontend *fe,
		int maxwait, int step, u8 irq)
{
	struct i2c_client *client = fe->tuner_priv;
	struct tda18250_dev *dev = i2c_get_clientdata(client);
	int ret;
	unsigned long timeout;
	bool triggered;
	unsigned int utmp;

	triggered = false;
	timeout = jiffies + msecs_to_jiffies(maxwait);
	while (!time_after(jiffies, timeout)) {
		// check for the IRQ
		ret = regmap_read(dev->regmap, R08_IRQ1, &utmp);
		if (ret)
			goto err;
		if ((utmp & irq) == irq) {
			triggered = true;
			break;
		}
		msleep(step);
	}

	dev_dbg(&client->dev, "waited IRQ (0x%02x) %d ms, triggered: %s", irq,
			jiffies_to_msecs(jiffies) -
			(jiffies_to_msecs(timeout) - maxwait),
			triggered ? "true" : "false");

	if (!triggered)
		return -ETIMEDOUT;

	return 0;
err:
	return ret;
}