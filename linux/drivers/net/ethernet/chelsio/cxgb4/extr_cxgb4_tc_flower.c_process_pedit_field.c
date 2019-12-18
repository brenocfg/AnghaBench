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
struct ch_filter_specification {int newdmac; int newsmac; void* nat_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DMAC_31_0 ; 
 int /*<<< orphan*/  ETH_DMAC_47_32 ; 
 int /*<<< orphan*/  ETH_SMAC_15_0 ; 
 int /*<<< orphan*/  ETH_SMAC_47_16 ; 
#define  FLOW_ACT_MANGLE_HDR_TYPE_ETH 147 
#define  FLOW_ACT_MANGLE_HDR_TYPE_IP4 146 
#define  FLOW_ACT_MANGLE_HDR_TYPE_IP6 145 
#define  FLOW_ACT_MANGLE_HDR_TYPE_TCP 144 
#define  FLOW_ACT_MANGLE_HDR_TYPE_UDP 143 
 int /*<<< orphan*/  IP4_DST ; 
 int /*<<< orphan*/  IP4_SRC ; 
 int /*<<< orphan*/  IP6_DST_127_96 ; 
 int /*<<< orphan*/  IP6_DST_31_0 ; 
 int /*<<< orphan*/  IP6_DST_63_32 ; 
 int /*<<< orphan*/  IP6_DST_95_64 ; 
 int /*<<< orphan*/  IP6_SRC_127_96 ; 
 int /*<<< orphan*/  IP6_SRC_31_0 ; 
 int /*<<< orphan*/  IP6_SRC_63_32 ; 
 int /*<<< orphan*/  IP6_SRC_95_64 ; 
 void* NAT_MODE_ALL ; 
#define  PEDIT_ETH_DMAC_31_0 142 
#define  PEDIT_ETH_DMAC_47_32_SMAC_15_0 141 
 int PEDIT_ETH_DMAC_MASK ; 
#define  PEDIT_ETH_SMAC_47_16 140 
#define  PEDIT_IP4_DST 139 
#define  PEDIT_IP4_SRC 138 
#define  PEDIT_IP6_DST_127_96 137 
#define  PEDIT_IP6_DST_31_0 136 
#define  PEDIT_IP6_DST_63_32 135 
#define  PEDIT_IP6_DST_95_64 134 
#define  PEDIT_IP6_SRC_127_96 133 
#define  PEDIT_IP6_SRC_31_0 132 
#define  PEDIT_IP6_SRC_63_32 131 
#define  PEDIT_IP6_SRC_95_64 130 
#define  PEDIT_TCP_SPORT_DPORT 129 
 int PEDIT_TCP_UDP_SPORT_MASK ; 
#define  PEDIT_UDP_SPORT_DPORT 128 
 int /*<<< orphan*/  TCP_DPORT ; 
 int /*<<< orphan*/  TCP_SPORT ; 
 int /*<<< orphan*/  UDP_DPORT ; 
 int /*<<< orphan*/  UDP_SPORT ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  offload_pedit (struct ch_filter_specification*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_pedit_field(struct ch_filter_specification *fs, u32 val,
				u32 mask, u32 offset, u8 htype)
{
	switch (htype) {
	case FLOW_ACT_MANGLE_HDR_TYPE_ETH:
		switch (offset) {
		case PEDIT_ETH_DMAC_31_0:
			fs->newdmac = 1;
			offload_pedit(fs, val, mask, ETH_DMAC_31_0);
			break;
		case PEDIT_ETH_DMAC_47_32_SMAC_15_0:
			if (~mask & PEDIT_ETH_DMAC_MASK)
				offload_pedit(fs, val, mask, ETH_DMAC_47_32);
			else
				offload_pedit(fs, val >> 16, mask >> 16,
					      ETH_SMAC_15_0);
			break;
		case PEDIT_ETH_SMAC_47_16:
			fs->newsmac = 1;
			offload_pedit(fs, val, mask, ETH_SMAC_47_16);
		}
		break;
	case FLOW_ACT_MANGLE_HDR_TYPE_IP4:
		switch (offset) {
		case PEDIT_IP4_SRC:
			offload_pedit(fs, val, mask, IP4_SRC);
			break;
		case PEDIT_IP4_DST:
			offload_pedit(fs, val, mask, IP4_DST);
		}
		fs->nat_mode = NAT_MODE_ALL;
		break;
	case FLOW_ACT_MANGLE_HDR_TYPE_IP6:
		switch (offset) {
		case PEDIT_IP6_SRC_31_0:
			offload_pedit(fs, val, mask, IP6_SRC_31_0);
			break;
		case PEDIT_IP6_SRC_63_32:
			offload_pedit(fs, val, mask, IP6_SRC_63_32);
			break;
		case PEDIT_IP6_SRC_95_64:
			offload_pedit(fs, val, mask, IP6_SRC_95_64);
			break;
		case PEDIT_IP6_SRC_127_96:
			offload_pedit(fs, val, mask, IP6_SRC_127_96);
			break;
		case PEDIT_IP6_DST_31_0:
			offload_pedit(fs, val, mask, IP6_DST_31_0);
			break;
		case PEDIT_IP6_DST_63_32:
			offload_pedit(fs, val, mask, IP6_DST_63_32);
			break;
		case PEDIT_IP6_DST_95_64:
			offload_pedit(fs, val, mask, IP6_DST_95_64);
			break;
		case PEDIT_IP6_DST_127_96:
			offload_pedit(fs, val, mask, IP6_DST_127_96);
		}
		fs->nat_mode = NAT_MODE_ALL;
		break;
	case FLOW_ACT_MANGLE_HDR_TYPE_TCP:
		switch (offset) {
		case PEDIT_TCP_SPORT_DPORT:
			if (~mask & PEDIT_TCP_UDP_SPORT_MASK)
				offload_pedit(fs, cpu_to_be32(val) >> 16,
					      cpu_to_be32(mask) >> 16,
					      TCP_SPORT);
			else
				offload_pedit(fs, cpu_to_be32(val),
					      cpu_to_be32(mask), TCP_DPORT);
		}
		fs->nat_mode = NAT_MODE_ALL;
		break;
	case FLOW_ACT_MANGLE_HDR_TYPE_UDP:
		switch (offset) {
		case PEDIT_UDP_SPORT_DPORT:
			if (~mask & PEDIT_TCP_UDP_SPORT_MASK)
				offload_pedit(fs, cpu_to_be32(val) >> 16,
					      cpu_to_be32(mask) >> 16,
					      UDP_SPORT);
			else
				offload_pedit(fs, cpu_to_be32(val),
					      cpu_to_be32(mask), UDP_DPORT);
		}
		fs->nat_mode = NAT_MODE_ALL;
	}
}