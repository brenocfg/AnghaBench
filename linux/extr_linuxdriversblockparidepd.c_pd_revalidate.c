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
struct pd_unit {int /*<<< orphan*/  capacity; } ;
struct gendisk {struct pd_unit* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pd_identify ; 
 scalar_t__ pd_special_command (struct pd_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pd_revalidate(struct gendisk *p)
{
	struct pd_unit *disk = p->private_data;
	if (pd_special_command(disk, pd_identify) == 0)
		set_capacity(p, disk->capacity);
	else
		set_capacity(p, 0);
	return 0;
}