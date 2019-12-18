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
struct myrs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYRS_IOCTL_FLUSH_DEVICE_DATA ; 
 int /*<<< orphan*/  MYRS_RAID_CONTROLLER ; 
 int /*<<< orphan*/  myrs_dev_op (struct myrs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void myrs_flush_cache(struct myrs_hba *cs)
{
	myrs_dev_op(cs, MYRS_IOCTL_FLUSH_DEVICE_DATA, MYRS_RAID_CONTROLLER);
}