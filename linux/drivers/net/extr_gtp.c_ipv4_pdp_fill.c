#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* o_tei; void* i_tei; } ;
struct TYPE_8__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  tid; } ;
struct TYPE_10__ {TYPE_4__ v1; TYPE_3__ v0; } ;
struct TYPE_7__ {void* s_addr; } ;
struct TYPE_6__ {void* s_addr; } ;
struct pdp_ctx {int gtp_version; TYPE_5__ u; TYPE_2__ ms_addr_ip4; TYPE_1__ peer_addr_ip4; int /*<<< orphan*/  af; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 size_t GTPA_FLOW ; 
 size_t GTPA_I_TEI ; 
 size_t GTPA_MS_ADDRESS ; 
 size_t GTPA_O_TEI ; 
 size_t GTPA_PEER_ADDRESS ; 
 size_t GTPA_TID ; 
 size_t GTPA_VERSION ; 
#define  GTP_V0 129 
#define  GTP_V1 128 
 void* nla_get_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (int /*<<< orphan*/ ) ; 
 void* nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipv4_pdp_fill(struct pdp_ctx *pctx, struct genl_info *info)
{
	pctx->gtp_version = nla_get_u32(info->attrs[GTPA_VERSION]);
	pctx->af = AF_INET;
	pctx->peer_addr_ip4.s_addr =
		nla_get_be32(info->attrs[GTPA_PEER_ADDRESS]);
	pctx->ms_addr_ip4.s_addr =
		nla_get_be32(info->attrs[GTPA_MS_ADDRESS]);

	switch (pctx->gtp_version) {
	case GTP_V0:
		/* According to TS 09.60, sections 7.5.1 and 7.5.2, the flow
		 * label needs to be the same for uplink and downlink packets,
		 * so let's annotate this.
		 */
		pctx->u.v0.tid = nla_get_u64(info->attrs[GTPA_TID]);
		pctx->u.v0.flow = nla_get_u16(info->attrs[GTPA_FLOW]);
		break;
	case GTP_V1:
		pctx->u.v1.i_tei = nla_get_u32(info->attrs[GTPA_I_TEI]);
		pctx->u.v1.o_tei = nla_get_u32(info->attrs[GTPA_O_TEI]);
		break;
	default:
		break;
	}
}