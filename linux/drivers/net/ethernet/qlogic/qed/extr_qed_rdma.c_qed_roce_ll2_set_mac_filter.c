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
typedef  int /*<<< orphan*/  u8 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*) ; 
 int qed_llh_add_mac_filter (struct qed_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_llh_remove_mac_filter (struct qed_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_roce_ll2_set_mac_filter(struct qed_dev *cdev,
				       u8 *old_mac_address,
				       u8 *new_mac_address)
{
	int rc = 0;

	if (old_mac_address)
		qed_llh_remove_mac_filter(cdev, 0, old_mac_address);
	if (new_mac_address)
		rc = qed_llh_add_mac_filter(cdev, 0, new_mac_address);

	if (rc)
		DP_ERR(cdev,
		       "qed roce ll2 mac filter set: failed to add MAC filter\n");

	return rc;
}