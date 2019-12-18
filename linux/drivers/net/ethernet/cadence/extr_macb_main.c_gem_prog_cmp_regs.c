#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct macb {int dummy; } ;
struct ethtool_tcpip4_spec {int ip4src; int ip4dst; int psrc; int pdst; } ;
struct TYPE_4__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_3__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {int ring_cookie; TYPE_2__ m_u; TYPE_1__ h_u; int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPA ; 
 int /*<<< orphan*/  CMPB ; 
 int /*<<< orphan*/  CMPC ; 
 int /*<<< orphan*/  ETHT2IDX ; 
 int ETYPE_DSTIP_OFFSET ; 
 int ETYPE_SRCIP_OFFSET ; 
 int GEM_BFINS (int /*<<< orphan*/ ,int,int) ; 
 int GEM_IP4DST_CMP (int /*<<< orphan*/ ) ; 
 int GEM_IP4SRC_CMP (int /*<<< orphan*/ ) ; 
 int GEM_PORT_CMP (int /*<<< orphan*/ ) ; 
 int GEM_T2COMPOFST_ETYPE ; 
 int GEM_T2COMPOFST_IPHDR ; 
 int IPHDR_DSTPORT_OFFSET ; 
 int IPHDR_SRCPORT_OFFSET ; 
 int /*<<< orphan*/  QUEUE ; 
 int /*<<< orphan*/  SCRT2 ; 
 int SCRT2_ETHT ; 
 int /*<<< orphan*/  T2CMP ; 
 int /*<<< orphan*/  T2CMPOFST ; 
 int /*<<< orphan*/  T2CMPW0 ; 
 int /*<<< orphan*/  T2CMPW1 ; 
 int /*<<< orphan*/  T2CMP_OFST (int) ; 
 int /*<<< orphan*/  T2DISMSK ; 
 int /*<<< orphan*/  T2MASK ; 
 int /*<<< orphan*/  T2OFST ; 
 int /*<<< orphan*/  gem_writel_n (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gem_prog_cmp_regs(struct macb *bp, struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_tcpip4_spec *tp4sp_v, *tp4sp_m;
	uint16_t index = fs->location;
	u32 w0, w1, t2_scr;
	bool cmp_a = false;
	bool cmp_b = false;
	bool cmp_c = false;

	tp4sp_v = &(fs->h_u.tcp_ip4_spec);
	tp4sp_m = &(fs->m_u.tcp_ip4_spec);

	/* ignore field if any masking set */
	if (tp4sp_m->ip4src == 0xFFFFFFFF) {
		/* 1st compare reg - IP source address */
		w0 = 0;
		w1 = 0;
		w0 = tp4sp_v->ip4src;
		w1 = GEM_BFINS(T2DISMSK, 1, w1); /* 32-bit compare */
		w1 = GEM_BFINS(T2CMPOFST, GEM_T2COMPOFST_ETYPE, w1);
		w1 = GEM_BFINS(T2OFST, ETYPE_SRCIP_OFFSET, w1);
		gem_writel_n(bp, T2CMPW0, T2CMP_OFST(GEM_IP4SRC_CMP(index)), w0);
		gem_writel_n(bp, T2CMPW1, T2CMP_OFST(GEM_IP4SRC_CMP(index)), w1);
		cmp_a = true;
	}

	/* ignore field if any masking set */
	if (tp4sp_m->ip4dst == 0xFFFFFFFF) {
		/* 2nd compare reg - IP destination address */
		w0 = 0;
		w1 = 0;
		w0 = tp4sp_v->ip4dst;
		w1 = GEM_BFINS(T2DISMSK, 1, w1); /* 32-bit compare */
		w1 = GEM_BFINS(T2CMPOFST, GEM_T2COMPOFST_ETYPE, w1);
		w1 = GEM_BFINS(T2OFST, ETYPE_DSTIP_OFFSET, w1);
		gem_writel_n(bp, T2CMPW0, T2CMP_OFST(GEM_IP4DST_CMP(index)), w0);
		gem_writel_n(bp, T2CMPW1, T2CMP_OFST(GEM_IP4DST_CMP(index)), w1);
		cmp_b = true;
	}

	/* ignore both port fields if masking set in both */
	if ((tp4sp_m->psrc == 0xFFFF) || (tp4sp_m->pdst == 0xFFFF)) {
		/* 3rd compare reg - source port, destination port */
		w0 = 0;
		w1 = 0;
		w1 = GEM_BFINS(T2CMPOFST, GEM_T2COMPOFST_IPHDR, w1);
		if (tp4sp_m->psrc == tp4sp_m->pdst) {
			w0 = GEM_BFINS(T2MASK, tp4sp_v->psrc, w0);
			w0 = GEM_BFINS(T2CMP, tp4sp_v->pdst, w0);
			w1 = GEM_BFINS(T2DISMSK, 1, w1); /* 32-bit compare */
			w1 = GEM_BFINS(T2OFST, IPHDR_SRCPORT_OFFSET, w1);
		} else {
			/* only one port definition */
			w1 = GEM_BFINS(T2DISMSK, 0, w1); /* 16-bit compare */
			w0 = GEM_BFINS(T2MASK, 0xFFFF, w0);
			if (tp4sp_m->psrc == 0xFFFF) { /* src port */
				w0 = GEM_BFINS(T2CMP, tp4sp_v->psrc, w0);
				w1 = GEM_BFINS(T2OFST, IPHDR_SRCPORT_OFFSET, w1);
			} else { /* dst port */
				w0 = GEM_BFINS(T2CMP, tp4sp_v->pdst, w0);
				w1 = GEM_BFINS(T2OFST, IPHDR_DSTPORT_OFFSET, w1);
			}
		}
		gem_writel_n(bp, T2CMPW0, T2CMP_OFST(GEM_PORT_CMP(index)), w0);
		gem_writel_n(bp, T2CMPW1, T2CMP_OFST(GEM_PORT_CMP(index)), w1);
		cmp_c = true;
	}

	t2_scr = 0;
	t2_scr = GEM_BFINS(QUEUE, (fs->ring_cookie) & 0xFF, t2_scr);
	t2_scr = GEM_BFINS(ETHT2IDX, SCRT2_ETHT, t2_scr);
	if (cmp_a)
		t2_scr = GEM_BFINS(CMPA, GEM_IP4SRC_CMP(index), t2_scr);
	if (cmp_b)
		t2_scr = GEM_BFINS(CMPB, GEM_IP4DST_CMP(index), t2_scr);
	if (cmp_c)
		t2_scr = GEM_BFINS(CMPC, GEM_PORT_CMP(index), t2_scr);
	gem_writel_n(bp, SCRT2, index, t2_scr);
}