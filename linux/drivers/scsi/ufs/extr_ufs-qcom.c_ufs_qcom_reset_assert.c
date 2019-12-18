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
struct ufs_qcom_host {int /*<<< orphan*/  hba; } ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 struct ufs_qcom_host* rcdev_to_ufs_host (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  ufs_qcom_assert_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ufs_qcom_reset_assert(struct reset_controller_dev *rcdev, unsigned long id)
{
	struct ufs_qcom_host *host = rcdev_to_ufs_host(rcdev);

	/* Currently this code only knows about a single reset. */
	WARN_ON(id);
	ufs_qcom_assert_reset(host->hba);
	/* provide 1ms delay to let the reset pulse propagate. */
	usleep_range(1000, 1100);
	return 0;
}