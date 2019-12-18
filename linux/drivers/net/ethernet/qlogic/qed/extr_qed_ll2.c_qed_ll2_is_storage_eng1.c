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
struct qed_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ QED_AFFIN_HWFN (struct qed_dev*) ; 
 scalar_t__ QED_IS_FCOE_PERSONALITY (scalar_t__) ; 
 scalar_t__ QED_IS_ISCSI_PERSONALITY (scalar_t__) ; 
 scalar_t__ QED_LEADING_HWFN (struct qed_dev*) ; 

__attribute__((used)) static bool qed_ll2_is_storage_eng1(struct qed_dev *cdev)
{
	return (QED_IS_FCOE_PERSONALITY(QED_LEADING_HWFN(cdev)) ||
		QED_IS_ISCSI_PERSONALITY(QED_LEADING_HWFN(cdev))) &&
		(QED_AFFIN_HWFN(cdev) != QED_LEADING_HWFN(cdev));
}