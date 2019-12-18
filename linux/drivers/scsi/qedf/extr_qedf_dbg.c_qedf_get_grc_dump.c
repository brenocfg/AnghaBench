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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct qed_dev {int dummy; } ;
struct qed_common_ops {int (* dbg_all_data ) (struct qed_dev*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct qed_dev*,int /*<<< orphan*/ *) ; 

int
qedf_get_grc_dump(struct qed_dev *cdev, const struct qed_common_ops *common,
		   u8 **buf, uint32_t *grcsize)
{
	if (!*buf)
		return -EINVAL;

	return common->dbg_all_data(cdev, *buf);
}