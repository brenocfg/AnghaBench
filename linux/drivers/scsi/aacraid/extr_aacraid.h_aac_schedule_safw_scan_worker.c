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
struct aac_dev {int /*<<< orphan*/  safw_rescan_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_SAFW_RESCAN_DELAY ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aac_schedule_safw_scan_worker(struct aac_dev *dev)
{
	schedule_delayed_work(&dev->safw_rescan_work, AAC_SAFW_RESCAN_DELAY);
}