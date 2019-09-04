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
struct qed_chain {int mode; } ;

/* Variables and functions */
#define  QED_CHAIN_MODE_NEXT_PTR 130 
#define  QED_CHAIN_MODE_PBL 129 
#define  QED_CHAIN_MODE_SINGLE 128 
 int /*<<< orphan*/  qed_chain_free_next_ptr (struct qed_dev*,struct qed_chain*) ; 
 int /*<<< orphan*/  qed_chain_free_pbl (struct qed_dev*,struct qed_chain*) ; 
 int /*<<< orphan*/  qed_chain_free_single (struct qed_dev*,struct qed_chain*) ; 

void qed_chain_free(struct qed_dev *cdev, struct qed_chain *p_chain)
{
	switch (p_chain->mode) {
	case QED_CHAIN_MODE_NEXT_PTR:
		qed_chain_free_next_ptr(cdev, p_chain);
		break;
	case QED_CHAIN_MODE_SINGLE:
		qed_chain_free_single(cdev, p_chain);
		break;
	case QED_CHAIN_MODE_PBL:
		qed_chain_free_pbl(cdev, p_chain);
		break;
	}
}