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
typedef  int /*<<< orphan*/  u32 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FEATURE_IDLE_CHK ; 
 int qed_dbg_feature (struct qed_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_dbg_idle_chk(struct qed_dev *cdev, void *buffer, u32 *num_dumped_bytes)
{
	return qed_dbg_feature(cdev, buffer, DBG_FEATURE_IDLE_CHK,
			       num_dumped_bytes);
}