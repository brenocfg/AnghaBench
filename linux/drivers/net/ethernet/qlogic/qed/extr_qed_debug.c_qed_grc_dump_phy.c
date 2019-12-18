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
typedef  size_t u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct phy_defs {int base_addr; int tbus_addr_lo_addr; int tbus_addr_hi_addr; int tbus_data_lo_addr; int tbus_data_hi_addr; char* phy_name; } ;
typedef  int /*<<< orphan*/  mem_name ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct phy_defs*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int NUM_PHY_TBUS_ADDRESSES ; 
 int PHY_DUMP_SIZE_DWORDS ; 
 int qed_grc_dump_mem_hdr (struct qed_hwfn*,int*,int,char*,int /*<<< orphan*/ ,int,int,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int,int) ; 
 struct phy_defs* s_phy_defs ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static u32 qed_grc_dump_phy(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt, u32 *dump_buf, bool dump)
{
	u32 offset = 0, tbus_lo_offset, tbus_hi_offset;
	char mem_name[32];
	u8 phy_id;

	for (phy_id = 0; phy_id < ARRAY_SIZE(s_phy_defs); phy_id++) {
		u32 addr_lo_addr, addr_hi_addr, data_lo_addr, data_hi_addr;
		struct phy_defs *phy_defs;
		u8 *bytes_buf;

		phy_defs = &s_phy_defs[phy_id];
		addr_lo_addr = phy_defs->base_addr +
			       phy_defs->tbus_addr_lo_addr;
		addr_hi_addr = phy_defs->base_addr +
			       phy_defs->tbus_addr_hi_addr;
		data_lo_addr = phy_defs->base_addr +
			       phy_defs->tbus_data_lo_addr;
		data_hi_addr = phy_defs->base_addr +
			       phy_defs->tbus_data_hi_addr;

		if (snprintf(mem_name, sizeof(mem_name), "tbus_%s",
			     phy_defs->phy_name) < 0)
			DP_NOTICE(p_hwfn,
				  "Unexpected debug error: invalid PHY memory name\n");

		offset += qed_grc_dump_mem_hdr(p_hwfn,
					       dump_buf + offset,
					       dump,
					       mem_name,
					       0,
					       PHY_DUMP_SIZE_DWORDS,
					       16, true, mem_name, false, 0);

		if (!dump) {
			offset += PHY_DUMP_SIZE_DWORDS;
			continue;
		}

		bytes_buf = (u8 *)(dump_buf + offset);
		for (tbus_hi_offset = 0;
		     tbus_hi_offset < (NUM_PHY_TBUS_ADDRESSES >> 8);
		     tbus_hi_offset++) {
			qed_wr(p_hwfn, p_ptt, addr_hi_addr, tbus_hi_offset);
			for (tbus_lo_offset = 0; tbus_lo_offset < 256;
			     tbus_lo_offset++) {
				qed_wr(p_hwfn,
				       p_ptt, addr_lo_addr, tbus_lo_offset);
				*(bytes_buf++) = (u8)qed_rd(p_hwfn,
							    p_ptt,
							    data_lo_addr);
				*(bytes_buf++) = (u8)qed_rd(p_hwfn,
							    p_ptt,
							    data_hi_addr);
			}
		}

		offset += PHY_DUMP_SIZE_DWORDS;
	}

	return offset;
}