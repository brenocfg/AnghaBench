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
struct gru_state {unsigned long gs_gru_base_paddr; int gs_gid; int gs_blade_id; int gs_chiplet_id; unsigned long gs_cbr_map; unsigned long gs_dsr_map; void* gs_gru_base_vaddr; int /*<<< orphan*/  gs_asid_limit; int /*<<< orphan*/  gs_blade; int /*<<< orphan*/  gs_asid_lock; int /*<<< orphan*/  gs_lock; } ;

/* Variables and functions */
 int GRU_CBR_AU ; 
 int GRU_CHIPLETS_PER_BLADE ; 
 unsigned long GRU_DSR_AU ; 
 int /*<<< orphan*/  MAX_ASID ; 
 int /*<<< orphan*/ * gru_base ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,int,int,void*,unsigned long) ; 
 int gru_max_gids ; 
 int /*<<< orphan*/  gru_tgh_flush_init (struct gru_state*) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gru_init_chiplet(struct gru_state *gru, unsigned long paddr,
			     void *vaddr, int blade_id, int chiplet_id)
{
	spin_lock_init(&gru->gs_lock);
	spin_lock_init(&gru->gs_asid_lock);
	gru->gs_gru_base_paddr = paddr;
	gru->gs_gru_base_vaddr = vaddr;
	gru->gs_gid = blade_id * GRU_CHIPLETS_PER_BLADE + chiplet_id;
	gru->gs_blade = gru_base[blade_id];
	gru->gs_blade_id = blade_id;
	gru->gs_chiplet_id = chiplet_id;
	gru->gs_cbr_map = (GRU_CBR_AU == 64) ? ~0 : (1UL << GRU_CBR_AU) - 1;
	gru->gs_dsr_map = (1UL << GRU_DSR_AU) - 1;
	gru->gs_asid_limit = MAX_ASID;
	gru_tgh_flush_init(gru);
	if (gru->gs_gid >= gru_max_gids)
		gru_max_gids = gru->gs_gid + 1;
	gru_dbg(grudev, "bid %d, gid %d, vaddr %p (0x%lx)\n",
		blade_id, gru->gs_gid, gru->gs_gru_base_vaddr,
		gru->gs_gru_base_paddr);
}