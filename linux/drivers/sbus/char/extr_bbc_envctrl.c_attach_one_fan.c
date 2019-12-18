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
struct platform_device {int dummy; } ;
struct bbc_i2c_bus {int /*<<< orphan*/  fans; } ;
struct bbc_fan_control {int index; int psupply_fan_on; int cpu_fan_speed; int system_fan_speed; int /*<<< orphan*/  bp_list; int /*<<< orphan*/  glob_list; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int FAN_SPEED_MAX ; 
 int FAN_SPEED_MIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_fans ; 
 int /*<<< orphan*/  bbc_i2c_attach (struct bbc_i2c_bus*,struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct bbc_fan_control*) ; 
 struct bbc_fan_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fan_speeds (struct bbc_fan_control*) ; 

__attribute__((used)) static void attach_one_fan(struct bbc_i2c_bus *bp, struct platform_device *op,
			   int fan_idx)
{
	struct bbc_fan_control *fp;

	fp = kzalloc(sizeof(*fp), GFP_KERNEL);
	if (!fp)
		return;

	INIT_LIST_HEAD(&fp->bp_list);
	INIT_LIST_HEAD(&fp->glob_list);

	fp->client = bbc_i2c_attach(bp, op);
	if (!fp->client) {
		kfree(fp);
		return;
	}

	fp->index = fan_idx;

	list_add(&fp->glob_list, &all_fans);
	list_add(&fp->bp_list, &bp->fans);

	/* The i2c device controlling the fans is write-only.
	 * So the only way to keep track of the current power
	 * level fed to the fans is via software.  Choose half
	 * power for cpu/system and 'on' fo the powersupply fan
	 * and set it now.
	 */
	fp->psupply_fan_on = 1;
	fp->cpu_fan_speed = (FAN_SPEED_MAX - FAN_SPEED_MIN) / 2;
	fp->cpu_fan_speed += FAN_SPEED_MIN;
	fp->system_fan_speed = (FAN_SPEED_MAX - FAN_SPEED_MIN) / 2;
	fp->system_fan_speed += FAN_SPEED_MIN;

	set_fan_speeds(fp);
}