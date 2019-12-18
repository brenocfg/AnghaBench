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
struct w1_master {int slave_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  W1_RESUME_CMD ; 
 int /*<<< orphan*/  W1_SKIP_ROM ; 
 scalar_t__ w1_reset_bus (struct w1_master*) ; 
 int /*<<< orphan*/  w1_write_8 (struct w1_master*,int /*<<< orphan*/ ) ; 

int w1_reset_resume_command(struct w1_master *dev)
{
	if (w1_reset_bus(dev))
		return -1;

	w1_write_8(dev, dev->slave_count > 1 ? W1_RESUME_CMD : W1_SKIP_ROM);
	return 0;
}