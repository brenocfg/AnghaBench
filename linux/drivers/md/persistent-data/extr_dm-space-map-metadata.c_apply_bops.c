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
struct sm_metadata {int /*<<< orphan*/  uncommitted; } ;
struct block_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  brb_empty (int /*<<< orphan*/ *) ; 
 int brb_peek (int /*<<< orphan*/ *,struct block_op*) ; 
 int /*<<< orphan*/  brb_pop (int /*<<< orphan*/ *) ; 
 int commit_bop (struct sm_metadata*,struct block_op*) ; 

__attribute__((used)) static int apply_bops(struct sm_metadata *smm)
{
	int r = 0;

	while (!brb_empty(&smm->uncommitted)) {
		struct block_op bop;

		r = brb_peek(&smm->uncommitted, &bop);
		if (r) {
			DMERR("bug in bop ring buffer");
			break;
		}

		r = commit_bop(smm, &bop);
		if (r)
			break;

		brb_pop(&smm->uncommitted);
	}

	return r;
}