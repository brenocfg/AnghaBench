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
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct et8ek8_reg {scalar_t__ type; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ ET8EK8_REG_16BIT ; 
 scalar_t__ ET8EK8_REG_8BIT ; 
 scalar_t__ ET8EK8_REG_DELAY ; 
 scalar_t__ ET8EK8_REG_TERM ; 
 scalar_t__ WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int et8ek8_i2c_buffered_write_regs (struct i2c_client*,struct et8ek8_reg const*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int et8ek8_i2c_write_regs(struct i2c_client *client,
				 const struct et8ek8_reg *regs)
{
	int r, cnt = 0;
	const struct et8ek8_reg *next;

	if (!client->adapter)
		return -ENODEV;

	if (!regs)
		return -EINVAL;

	/* Initialize list pointers to the start of the list */
	next = regs;

	do {
		/*
		 * We have to go through the list to figure out how
		 * many regular writes we have in a row
		 */
		while (next->type != ET8EK8_REG_TERM &&
		       next->type != ET8EK8_REG_DELAY) {
			/*
			 * Here we check that the actual length fields
			 * are valid
			 */
			if (WARN(next->type != ET8EK8_REG_8BIT &&
				 next->type != ET8EK8_REG_16BIT,
				 "Invalid type = %d", next->type)) {
				return -EINVAL;
			}
			/*
			 * Increment count of successive writes and
			 * read pointer
			 */
			cnt++;
			next++;
		}

		/* Now we start writing ... */
		r = et8ek8_i2c_buffered_write_regs(client, regs, cnt);

		/* ... and then check that everything was OK */
		if (r < 0) {
			dev_err(&client->dev, "i2c transfer error!\n");
			return r;
		}

		/*
		 * If we ran into a sleep statement when going through
		 * the list, this is where we snooze for the required time
		 */
		if (next->type == ET8EK8_REG_DELAY) {
			msleep(next->val);
			/*
			 * ZZZ ...
			 * Update list pointers and cnt and start over ...
			 */
			next++;
			regs = next;
			cnt = 0;
		}
	} while (next->type != ET8EK8_REG_TERM);

	return 0;
}