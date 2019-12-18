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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rxe_pkt_info {scalar_t__ offset; scalar_t__ hdr; } ;
struct rxe_bth {int flags; void* apsn; void* qpn; int /*<<< orphan*/  pkey; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int BTH_ACK_MASK ; 
 int BTH_MIG_MASK ; 
 int BTH_PAD_MASK ; 
 int BTH_PSN_MASK ; 
 int BTH_QPN_MASK ; 
 int BTH_SE_MASK ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static inline void bth_init(struct rxe_pkt_info *pkt, u8 opcode, int se,
			    int mig, int pad, u16 pkey, u32 qpn, int ack_req,
			    u32 psn)
{
	struct rxe_bth *bth = (struct rxe_bth *)(pkt->hdr + pkt->offset);

	bth->opcode = opcode;
	bth->flags = (pad << 4) & BTH_PAD_MASK;
	if (se)
		bth->flags |= BTH_SE_MASK;
	if (mig)
		bth->flags |= BTH_MIG_MASK;
	bth->pkey = cpu_to_be16(pkey);
	bth->qpn = cpu_to_be32(qpn & BTH_QPN_MASK);
	psn &= BTH_PSN_MASK;
	if (ack_req)
		psn |= BTH_ACK_MASK;
	bth->apsn = cpu_to_be32(psn);
}