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
struct edma_chan {int /*<<< orphan*/  ecc; int /*<<< orphan*/  ch_num; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_EESR ; 
 int /*<<< orphan*/  edma_shadow0_write_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void edma_resume(struct edma_chan *echan)
{
	int channel = EDMA_CHAN_SLOT(echan->ch_num);
	unsigned int mask = BIT(channel & 0x1f);

	edma_shadow0_write_array(echan->ecc, SH_EESR, channel >> 5, mask);
}