#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {scalar_t__ keysize; } ;
struct TYPE_2__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int KEX_LD_CFG (int,int,int,int,int) ; 
 int /*<<< orphan*/  NIX_INTF_RX ; 
 int /*<<< orphan*/  NIX_INTF_TX ; 
 int /*<<< orphan*/  NPC_AF_CONST ; 
 int NPC_LID_LA ; 
 int NPC_LID_LB ; 
 int NPC_LID_LC ; 
 int NPC_LID_LD ; 
 int NPC_LT_LA_ETHER ; 
 int NPC_LT_LB_CTAG ; 
 int NPC_LT_LB_QINQ ; 
 int NPC_LT_LB_STAG ; 
 int NPC_LT_LC_IP ; 
 int NPC_LT_LD_TCP ; 
 int NPC_LT_LD_UDP ; 
 scalar_t__ NPC_MCAM_KEY_X2 ; 
 int NPC_PARSE_RESULT_DMAC_OFFSET ; 
 int /*<<< orphan*/  SET_KEX_LD (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SET_KEX_LDFLAGS (int /*<<< orphan*/ ,int,int,unsigned long long) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npc_config_ldata_extract(struct rvu *rvu, int blkaddr)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	int lid, ltype;
	int lid_count;
	u64 cfg;

	cfg = rvu_read64(rvu, blkaddr, NPC_AF_CONST);
	lid_count = (cfg >> 4) & 0xF;

	/* First clear any existing config i.e
	 * disable LDATA and FLAGS extraction.
	 */
	for (lid = 0; lid < lid_count; lid++) {
		for (ltype = 0; ltype < 16; ltype++) {
			SET_KEX_LD(NIX_INTF_RX, lid, ltype, 0, 0ULL);
			SET_KEX_LD(NIX_INTF_RX, lid, ltype, 1, 0ULL);
			SET_KEX_LD(NIX_INTF_TX, lid, ltype, 0, 0ULL);
			SET_KEX_LD(NIX_INTF_TX, lid, ltype, 1, 0ULL);

			SET_KEX_LDFLAGS(NIX_INTF_RX, 0, ltype, 0ULL);
			SET_KEX_LDFLAGS(NIX_INTF_RX, 1, ltype, 0ULL);
			SET_KEX_LDFLAGS(NIX_INTF_TX, 0, ltype, 0ULL);
			SET_KEX_LDFLAGS(NIX_INTF_TX, 1, ltype, 0ULL);
		}
	}

	if (mcam->keysize != NPC_MCAM_KEY_X2)
		return;

	/* Default MCAM KEX profile */
	/* Layer A: Ethernet: */

	/* DMAC: 6 bytes, KW1[47:0] */
	cfg = KEX_LD_CFG(0x05, 0x0, 0x1, 0x0, NPC_PARSE_RESULT_DMAC_OFFSET);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LA, NPC_LT_LA_ETHER, 0, cfg);

	/* Ethertype: 2 bytes, KW0[47:32] */
	cfg = KEX_LD_CFG(0x01, 0xc, 0x1, 0x0, 0x4);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LA, NPC_LT_LA_ETHER, 1, cfg);

	/* Layer B: Single VLAN (CTAG) */
	/* CTAG VLAN[2..3] + Ethertype, 4 bytes, KW0[63:32] */
	cfg = KEX_LD_CFG(0x03, 0x0, 0x1, 0x0, 0x4);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LB, NPC_LT_LB_CTAG, 0, cfg);

	/* Layer B: Stacked VLAN (STAG|QinQ) */
	/* CTAG VLAN[2..3] + Ethertype, 4 bytes, KW0[63:32] */
	cfg = KEX_LD_CFG(0x03, 0x4, 0x1, 0x0, 0x4);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LB, NPC_LT_LB_STAG, 0, cfg);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LB, NPC_LT_LB_QINQ, 0, cfg);

	/* Layer C: IPv4 */
	/* SIP+DIP: 8 bytes, KW2[63:0] */
	cfg = KEX_LD_CFG(0x07, 0xc, 0x1, 0x0, 0x10);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LC, NPC_LT_LC_IP, 0, cfg);
	/* TOS: 1 byte, KW1[63:56] */
	cfg = KEX_LD_CFG(0x0, 0x1, 0x1, 0x0, 0xf);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LC, NPC_LT_LC_IP, 1, cfg);

	/* Layer D:UDP */
	/* SPORT: 2 bytes, KW3[15:0] */
	cfg = KEX_LD_CFG(0x1, 0x0, 0x1, 0x0, 0x18);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LD, NPC_LT_LD_UDP, 0, cfg);
	/* DPORT: 2 bytes, KW3[31:16] */
	cfg = KEX_LD_CFG(0x1, 0x2, 0x1, 0x0, 0x1a);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LD, NPC_LT_LD_UDP, 1, cfg);

	/* Layer D:TCP */
	/* SPORT: 2 bytes, KW3[15:0] */
	cfg = KEX_LD_CFG(0x1, 0x0, 0x1, 0x0, 0x18);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LD, NPC_LT_LD_TCP, 0, cfg);
	/* DPORT: 2 bytes, KW3[31:16] */
	cfg = KEX_LD_CFG(0x1, 0x2, 0x1, 0x0, 0x1a);
	SET_KEX_LD(NIX_INTF_RX, NPC_LID_LD, NPC_LT_LD_TCP, 1, cfg);
}