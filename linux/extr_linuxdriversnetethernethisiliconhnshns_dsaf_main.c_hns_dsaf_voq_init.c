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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_dsaf_voq_bp_all_thrd_cfg (struct dsaf_device*) ; 

__attribute__((used)) static void hns_dsaf_voq_init(struct dsaf_device *dsaf_dev)
{
	hns_dsaf_voq_bp_all_thrd_cfg(dsaf_dev);
}