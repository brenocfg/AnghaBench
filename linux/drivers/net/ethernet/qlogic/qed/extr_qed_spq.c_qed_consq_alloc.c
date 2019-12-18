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
struct qed_hwfn {struct qed_consq* p_consq; int /*<<< orphan*/  cdev; } ;
struct qed_consq {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_PBL ; 
 int QED_CHAIN_PAGE_SIZE ; 
 int /*<<< orphan*/  QED_CHAIN_USE_TO_PRODUCE ; 
 int /*<<< orphan*/  kfree (struct qed_consq*) ; 
 struct qed_consq* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_consq_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_consq *p_consq;

	/* Allocate ConsQ struct */
	p_consq = kzalloc(sizeof(*p_consq), GFP_KERNEL);
	if (!p_consq)
		return -ENOMEM;

	/* Allocate and initialize EQ chain*/
	if (qed_chain_alloc(p_hwfn->cdev,
			    QED_CHAIN_USE_TO_PRODUCE,
			    QED_CHAIN_MODE_PBL,
			    QED_CHAIN_CNT_TYPE_U16,
			    QED_CHAIN_PAGE_SIZE / 0x80,
			    0x80, &p_consq->chain, NULL))
		goto consq_allocate_fail;

	p_hwfn->p_consq = p_consq;
	return 0;

consq_allocate_fail:
	kfree(p_consq);
	return -ENOMEM;
}