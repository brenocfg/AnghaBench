#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent_sq; } ;
struct throtl_grp {int* has_rules; struct throtl_data* td; TYPE_1__ service_queue; } ;
struct throtl_data {size_t limit_index; scalar_t__* limit_valid; } ;

/* Variables and functions */
 int READ ; 
 scalar_t__ U64_MAX ; 
 scalar_t__ UINT_MAX ; 
 int WRITE ; 
 struct throtl_grp* sq_to_tg (int /*<<< orphan*/ ) ; 
 scalar_t__ tg_bps_limit (struct throtl_grp*,int) ; 
 scalar_t__ tg_iops_limit (struct throtl_grp*,int) ; 

__attribute__((used)) static void tg_update_has_rules(struct throtl_grp *tg)
{
	struct throtl_grp *parent_tg = sq_to_tg(tg->service_queue.parent_sq);
	struct throtl_data *td = tg->td;
	int rw;

	for (rw = READ; rw <= WRITE; rw++)
		tg->has_rules[rw] = (parent_tg && parent_tg->has_rules[rw]) ||
			(td->limit_valid[td->limit_index] &&
			 (tg_bps_limit(tg, rw) != U64_MAX ||
			  tg_iops_limit(tg, rw) != UINT_MAX));
}