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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_clear_vnic (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_free_tunnel_ports (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_ring_free (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_ring_grp_free (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_stat_ctx_free (struct bnxt*) ; 

__attribute__((used)) static void bnxt_hwrm_resource_free(struct bnxt *bp, bool close_path,
				    bool irq_re_init)
{
	bnxt_clear_vnic(bp);
	bnxt_hwrm_ring_free(bp, close_path);
	bnxt_hwrm_ring_grp_free(bp);
	if (irq_re_init) {
		bnxt_hwrm_stat_ctx_free(bp);
		bnxt_hwrm_free_tunnel_ports(bp);
	}
}