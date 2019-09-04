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
struct at_lli {int /*<<< orphan*/  dscr; int /*<<< orphan*/  ctrlb; int /*<<< orphan*/  ctrla; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct at_dma_chan {int /*<<< orphan*/  chan_common; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_dump_lli(struct at_dma_chan *atchan, struct at_lli *lli)
{
	dev_crit(chan2dev(&atchan->chan_common),
		 "desc: s%pad d%pad ctrl0x%x:0x%x l%pad\n",
		 &lli->saddr, &lli->daddr,
		 lli->ctrla, lli->ctrlb, &lli->dscr);
}