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
struct mvpp2_prs_entry {int index; int* sram; } ;
struct mvpp2 {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  pe ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short IPPROTO_IGMP ; 
 unsigned short IPPROTO_TCP ; 
 unsigned short IPPROTO_UDP ; 
 int /*<<< orphan*/  MVPP2_PE_FIRST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PE_LAST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PRS_IPV4_DIP_AI_BIT ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_IP4 ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 unsigned int MVPP2_PRS_RI_IP_FRAG_MASK ; 
 unsigned int MVPP2_PRS_RI_IP_FRAG_TRUE ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD ; 
 size_t MVPP2_PRS_SRAM_RI_CTRL_WORD ; 
 size_t MVPP2_PRS_SRAM_RI_WORD ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_UDF_TYPE_L4 ; 
 int MVPP2_PRS_TCAM_PROTO_MASK ; 
 int MVPP2_PRS_TCAM_PROTO_MASK_L ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_offset_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_set (struct mvpp2_prs_entry*,int,int,int) ; 
 int mvpp2_prs_tcam_first_free (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_prs_ip4_proto(struct mvpp2 *priv, unsigned short proto,
			       unsigned int ri, unsigned int ri_mask)
{
	struct mvpp2_prs_entry pe;
	int tid;

	if ((proto != IPPROTO_TCP) && (proto != IPPROTO_UDP) &&
	    (proto != IPPROTO_IGMP))
		return -EINVAL;

	/* Not fragmented packet */
	tid = mvpp2_prs_tcam_first_free(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	if (tid < 0)
		return tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_IP4);
	pe.index = tid;

	/* Set next lu to IPv4 */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_IP4);
	mvpp2_prs_sram_shift_set(&pe, 12, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	/* Set L4 offset */
	mvpp2_prs_sram_offset_set(&pe, MVPP2_PRS_SRAM_UDF_TYPE_L4,
				  sizeof(struct iphdr) - 4,
				  MVPP2_PRS_SRAM_OP_SEL_UDF_ADD);
	mvpp2_prs_sram_ai_update(&pe, MVPP2_PRS_IPV4_DIP_AI_BIT,
				 MVPP2_PRS_IPV4_DIP_AI_BIT);
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask | MVPP2_PRS_RI_IP_FRAG_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 2, 0x00,
				     MVPP2_PRS_TCAM_PROTO_MASK_L);
	mvpp2_prs_tcam_data_byte_set(&pe, 3, 0x00,
				     MVPP2_PRS_TCAM_PROTO_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 5, proto, MVPP2_PRS_TCAM_PROTO_MASK);
	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_IPV4_DIP_AI_BIT);
	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_write(priv, &pe);

	/* Fragmented packet */
	tid = mvpp2_prs_tcam_first_free(priv, MVPP2_PE_FIRST_FREE_TID,
					MVPP2_PE_LAST_FREE_TID);
	if (tid < 0)
		return tid;

	pe.index = tid;
	/* Clear ri before updating */
	pe.sram[MVPP2_PRS_SRAM_RI_WORD] = 0x0;
	pe.sram[MVPP2_PRS_SRAM_RI_CTRL_WORD] = 0x0;
	mvpp2_prs_sram_ri_update(&pe, ri, ri_mask);

	mvpp2_prs_sram_ri_update(&pe, ri | MVPP2_PRS_RI_IP_FRAG_TRUE,
				 ri_mask | MVPP2_PRS_RI_IP_FRAG_MASK);

	mvpp2_prs_tcam_data_byte_set(&pe, 2, 0x00, 0x0);
	mvpp2_prs_tcam_data_byte_set(&pe, 3, 0x00, 0x0);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_IP4);
	mvpp2_prs_hw_write(priv, &pe);

	return 0;
}