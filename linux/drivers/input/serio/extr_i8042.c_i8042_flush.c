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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I8042_BUFFER_SIZE ; 
 unsigned char I8042_STR_AUXDATA ; 
 unsigned char I8042_STR_OBF ; 
 int /*<<< orphan*/  dbg (char*,unsigned char,char*) ; 
 int /*<<< orphan*/  i8042_lock ; 
 unsigned char i8042_read_data () ; 
 unsigned char i8042_read_status () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i8042_flush(void)
{
	unsigned long flags;
	unsigned char data, str;
	int count = 0;
	int retval = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	while ((str = i8042_read_status()) & I8042_STR_OBF) {
		if (count++ < I8042_BUFFER_SIZE) {
			udelay(50);
			data = i8042_read_data();
			dbg("%02x <- i8042 (flush, %s)\n",
			    data, str & I8042_STR_AUXDATA ? "aux" : "kbd");
		} else {
			retval = -EIO;
			break;
		}
	}

	spin_unlock_irqrestore(&i8042_lock, flags);

	return retval;
}