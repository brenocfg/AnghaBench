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
struct bnxt {scalar_t__ nge_port_cnt; scalar_t__ vxlan_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE ; 
 int /*<<< orphan*/  TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  bnxt_hwrm_tunnel_dst_port_free (struct bnxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_hwrm_free_tunnel_ports(struct bnxt *bp)
{
	if (bp->vxlan_port_cnt) {
		bnxt_hwrm_tunnel_dst_port_free(
			bp, TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN);
	}
	bp->vxlan_port_cnt = 0;
	if (bp->nge_port_cnt) {
		bnxt_hwrm_tunnel_dst_port_free(
			bp, TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE);
	}
	bp->nge_port_cnt = 0;
}