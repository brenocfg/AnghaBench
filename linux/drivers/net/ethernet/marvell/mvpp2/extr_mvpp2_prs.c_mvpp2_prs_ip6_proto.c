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
struct mvpp2_prs_entry {int index; } ;
struct mvpp2 {int dummy; } ;
struct ipv6hdr {int dummy; } ;
typedef  int /*<<< orphan*/  pe ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short IPPROTO_ICMPV6 ; 
 unsigned short IPPROTO_IPIP ; 
 unsigned short IPPROTO_TCP ; 
 unsigned short IPPROTO_UDP ; 
 int /*<<< orphan*/  MVPP2_PE_FIRST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PE_LAST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PRS_IPV6_NO_EXT_AI_BIT ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_FLOWS ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_IP6 ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_LU_GEN_BIT ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_UDF_TYPE_L4 ; 
 int /*<<< orphan*/  MVPP2_PRS_TCAM_PROTO_MASK ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_offset_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int mvpp2_prs_tcam_first_free (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_prs_ip6_proto(struct mvpp2 *priv, unsigned short proto,
			       unsigned int ri, unsigned int ri_mask)
{
	struct mvpp2_prs_entry pe;
	int tid;

	if ((proto != IPPROTO_TCP) && (proto != IPPROTO_UDP) &&
	    (proto != IPPROTO_ICMPV6) && (proto != IPPROTO_IPIP))
		return -EINVAL;

	tid = mvpp2_prs_tcam_first_free(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	if (tid < 0)
		return tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP6);
	pe.index = tid;

	/* Finished: go to flowid generation */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask);
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L4,
				  sizeof(struct ipv6hdr) - 6,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);

	mvpp2_prs_tcam_data_byte_set(&pe, 0, proto, MVPP2_PRS_TCAM_PROTO_MASK);
	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PRS_IPV6_NO_EXT_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Write HW */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_IP6);
	mvpp2_prs_hw_write(priv, &pe);

	return 0;
}