#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dsaf_device {TYPE_1__* misc_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dsaf_reset ) (struct dsaf_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dsaf_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_remove_hw(struct dsaf_device *dsaf_dev)
{
	/*reset*/
	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 0);
}