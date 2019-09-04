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
struct edma_chan {int /*<<< orphan*/  ch_num; struct edma_cc* ecc; } ;
struct edma_cc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_ESR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_shadow0_read_array (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void edma_trigger_channel(struct edma_chan *echan)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);
	unsigned int mask = BIT(channel & 0x1f);

	edma_shadow0_write_array(ecc, SH_ESR, (channel >> 5), mask);

	dev_dbg(ecc->dev, "ESR%d %08x\n", (channel >> 5),
		edma_shadow0_read_array(ecc, SH_ESR, (channel >> 5)));
}