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
struct gru_blade_state {TYPE_1__* bs_kgts; int /*<<< orphan*/  bs_kgts_sema; } ;
struct TYPE_2__ {int /*<<< orphan*/  ts_gru; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct gru_blade_state** gru_base ; 
 int /*<<< orphan*/  gru_load_kernel_context (struct gru_blade_state*,int) ; 
 int /*<<< orphan*/  lock_kernel_context ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int uv_numa_blade_id () ; 

__attribute__((used)) static struct gru_blade_state *gru_lock_kernel_context(int blade_id)
{
	struct gru_blade_state *bs;
	int bid;

	STAT(lock_kernel_context);
again:
	bid = blade_id < 0 ? uv_numa_blade_id() : blade_id;
	bs = gru_base[bid];

	/* Handle the case where migration occurred while waiting for the sema */
	down_read(&bs->bs_kgts_sema);
	if (blade_id < 0 && bid != uv_numa_blade_id()) {
		up_read(&bs->bs_kgts_sema);
		goto again;
	}
	if (!bs->bs_kgts || !bs->bs_kgts->ts_gru)
		gru_load_kernel_context(bs, bid);
	return bs;

}