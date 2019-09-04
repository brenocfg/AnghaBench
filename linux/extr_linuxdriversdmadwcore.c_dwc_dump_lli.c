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
struct dw_dma_chan {int /*<<< orphan*/  chan; } ;
struct dw_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctlhi ; 
 int /*<<< orphan*/  ctllo ; 
 int /*<<< orphan*/  dar ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lli_read (struct dw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llp ; 
 int /*<<< orphan*/  sar ; 

__attribute__((used)) static inline void dwc_dump_lli(struct dw_dma_chan *dwc, struct dw_desc *desc)
{
	dev_crit(chan2dev(&dwc->chan), "  desc: s0x%x d0x%x l0x%x c0x%x:%x\n",
		 lli_read(desc, sar),
		 lli_read(desc, dar),
		 lli_read(desc, llp),
		 lli_read(desc, ctlhi),
		 lli_read(desc, ctllo));
}