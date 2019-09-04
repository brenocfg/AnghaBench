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
struct dsgl_walk {int /*<<< orphan*/  nents; struct cpl_rx_phys_dsgl* dsgl; } ;
struct TYPE_2__ {int channel; scalar_t__ hash_val; int /*<<< orphan*/  qid; int /*<<< orphan*/  opcode; } ;
struct cpl_rx_phys_dsgl {TYPE_1__ rss_hdr_int; void* pcirlxorder_to_noofsgentr; void* op_to_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_RX_PHYS_ADDR ; 
 int /*<<< orphan*/  CPL_RX_PHYS_DSGL ; 
 int CPL_RX_PHYS_DSGL_DCAID_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_ISRDMA_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_NOOFSGENTR_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_OPCODE_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_PCINOSNOOP_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_PCIRLXORDER_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_PCITPHNTENB_V (int /*<<< orphan*/ ) ; 
 int CPL_RX_PHYS_DSGL_PCITPHNT_V (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 

__attribute__((used)) static inline void dsgl_walk_end(struct dsgl_walk *walk, unsigned short qid,
				 int pci_chan_id)
{
	struct cpl_rx_phys_dsgl *phys_cpl;

	phys_cpl = walk->dsgl;

	phys_cpl->op_to_tid = htonl(CPL_RX_PHYS_DSGL_OPCODE_V(CPL_RX_PHYS_DSGL)
				    | CPL_RX_PHYS_DSGL_ISRDMA_V(0));
	phys_cpl->pcirlxorder_to_noofsgentr =
		htonl(CPL_RX_PHYS_DSGL_PCIRLXORDER_V(0) |
		      CPL_RX_PHYS_DSGL_PCINOSNOOP_V(0) |
		      CPL_RX_PHYS_DSGL_PCITPHNTENB_V(0) |
		      CPL_RX_PHYS_DSGL_PCITPHNT_V(0) |
		      CPL_RX_PHYS_DSGL_DCAID_V(0) |
		      CPL_RX_PHYS_DSGL_NOOFSGENTR_V(walk->nents));
	phys_cpl->rss_hdr_int.opcode = CPL_RX_PHYS_ADDR;
	phys_cpl->rss_hdr_int.qid = htons(qid);
	phys_cpl->rss_hdr_int.hash_val = 0;
	phys_cpl->rss_hdr_int.channel = pci_chan_id;
}