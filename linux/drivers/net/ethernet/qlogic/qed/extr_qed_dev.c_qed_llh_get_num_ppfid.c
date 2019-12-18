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
typedef  int /*<<< orphan*/  u8 ;
struct qed_dev {TYPE_1__* p_llh_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_ppfid; } ;

/* Variables and functions */

u8 qed_llh_get_num_ppfid(struct qed_dev *cdev)
{
	return cdev->p_llh_info->num_ppfid;
}