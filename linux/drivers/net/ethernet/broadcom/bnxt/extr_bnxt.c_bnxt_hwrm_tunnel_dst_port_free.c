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
typedef  int u8 ;
typedef  int u32 ;
struct hwrm_tunnel_dst_port_free_input {int tunnel_type; int /*<<< orphan*/  tunnel_dst_port_id; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  dev; int /*<<< orphan*/  nge_fw_dst_port_id; int /*<<< orphan*/  vxlan_fw_dst_port_id; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_TUNNEL_DST_PORT_FREE ; 
#define  TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE 129 
#define  TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_tunnel_dst_port_free_input*,int /*<<< orphan*/ ,int,int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_tunnel_dst_port_free_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_hwrm_tunnel_dst_port_free(struct bnxt *bp, u8 tunnel_type)
{
	u32 rc = 0;
	struct hwrm_tunnel_dst_port_free_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_TUNNEL_DST_PORT_FREE, -1, -1);
	req.tunnel_type = tunnel_type;

	switch (tunnel_type) {
	case TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_VXLAN:
		req.tunnel_dst_port_id = bp->vxlan_fw_dst_port_id;
		break;
	case TUNNEL_DST_PORT_FREE_REQ_TUNNEL_TYPE_GENEVE:
		req.tunnel_dst_port_id = bp->nge_fw_dst_port_id;
		break;
	default:
		break;
	}

	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		netdev_err(bp->dev, "hwrm_tunnel_dst_port_free failed. rc:%d\n",
			   rc);
	return rc;
}