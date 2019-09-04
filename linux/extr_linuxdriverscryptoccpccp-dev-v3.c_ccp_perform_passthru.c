#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_15__ {int length; } ;
struct TYPE_13__ {int sb; TYPE_7__ dma; } ;
struct TYPE_14__ {int type; TYPE_5__ u; } ;
struct TYPE_11__ {int sb; TYPE_7__ dma; } ;
struct TYPE_12__ {int type; TYPE_3__ u; } ;
struct TYPE_9__ {int bit_mod; int byte_swap; } ;
struct TYPE_10__ {TYPE_1__ passthru; } ;
struct ccp_op {int sb_key; scalar_t__ eom; TYPE_6__ dst; TYPE_4__ src; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int CCP_ENGINE_PASSTHRU ; 
 int CCP_MEMTYPE_SB ; 
 int CCP_MEMTYPE_SYSTEM ; 
 int CCP_PASSTHRU_BITWISE_NOOP ; 
 int CCP_SB_BYTES ; 
 int REQ1_ENGINE_SHIFT ; 
 int REQ1_EOM ; 
 int REQ1_PT_BS_SHIFT ; 
 int REQ1_PT_BW_SHIFT ; 
 int REQ4_KSB_SHIFT ; 
 int REQ4_MEMTYPE_SHIFT ; 
 int REQ6_MEMTYPE_SHIFT ; 
 int ccp_addr_hi (TYPE_7__*) ; 
 int ccp_addr_lo (TYPE_7__*) ; 
 int ccp_do_cmd (struct ccp_op*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp_perform_passthru(struct ccp_op *op)
{
	u32 cr[6];

	/* Fill out the register contents for REQ1 through REQ6 */
	cr[0] = (CCP_ENGINE_PASSTHRU << REQ1_ENGINE_SHIFT)
		| (op->u.passthru.bit_mod << REQ1_PT_BW_SHIFT)
		| (op->u.passthru.byte_swap << REQ1_PT_BS_SHIFT);

	if (op->src.type == CCP_MEMTYPE_SYSTEM)
		cr[1] = op->src.u.dma.length - 1;
	else
		cr[1] = op->dst.u.dma.length - 1;

	if (op->src.type == CCP_MEMTYPE_SYSTEM) {
		cr[2] = ccp_addr_lo(&op->src.u.dma);
		cr[3] = (CCP_MEMTYPE_SYSTEM << REQ4_MEMTYPE_SHIFT)
			| ccp_addr_hi(&op->src.u.dma);

		if (op->u.passthru.bit_mod != CCP_PASSTHRU_BITWISE_NOOP)
			cr[3] |= (op->sb_key << REQ4_KSB_SHIFT);
	} else {
		cr[2] = op->src.u.sb * CCP_SB_BYTES;
		cr[3] = (CCP_MEMTYPE_SB << REQ4_MEMTYPE_SHIFT);
	}

	if (op->dst.type == CCP_MEMTYPE_SYSTEM) {
		cr[4] = ccp_addr_lo(&op->dst.u.dma);
		cr[5] = (CCP_MEMTYPE_SYSTEM << REQ6_MEMTYPE_SHIFT)
			| ccp_addr_hi(&op->dst.u.dma);
	} else {
		cr[4] = op->dst.u.sb * CCP_SB_BYTES;
		cr[5] = (CCP_MEMTYPE_SB << REQ6_MEMTYPE_SHIFT);
	}

	if (op->eom)
		cr[0] |= REQ1_EOM;

	return ccp_do_cmd(op, cr, ARRAY_SIZE(cr));
}