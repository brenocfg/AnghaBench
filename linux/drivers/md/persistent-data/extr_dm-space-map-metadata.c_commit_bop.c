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
struct sm_metadata {int /*<<< orphan*/  ll; } ;
struct block_op {int type; int /*<<< orphan*/  block; } ;
typedef  enum allocation_event { ____Placeholder_allocation_event } allocation_event ;

/* Variables and functions */
#define  BOP_DEC 129 
#define  BOP_INC 128 
 int sm_ll_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int sm_ll_inc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int commit_bop(struct sm_metadata *smm, struct block_op *op)
{
	int r = 0;
	enum allocation_event ev;

	switch (op->type) {
	case BOP_INC:
		r = sm_ll_inc(&smm->ll, op->block, &ev);
		break;

	case BOP_DEC:
		r = sm_ll_dec(&smm->ll, op->block, &ev);
		break;
	}

	return r;
}