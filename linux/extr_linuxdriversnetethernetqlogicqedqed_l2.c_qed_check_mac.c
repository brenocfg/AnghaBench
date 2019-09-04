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
struct qed_dev {int /*<<< orphan*/ * hwfns; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct qed_dev*) ; 
 int qed_vf_check_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool qed_check_mac(struct qed_dev *cdev, u8 *mac)
{
	if (IS_PF(cdev))
		return true;

	return qed_vf_check_mac(&cdev->hwfns[0], mac);
}