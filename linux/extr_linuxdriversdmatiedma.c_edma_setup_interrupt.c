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
struct edma_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_ICR ; 
 int /*<<< orphan*/  SH_IECR ; 
 int /*<<< orphan*/  SH_IESR ; 
 int /*<<< orphan*/  edma_shadow0_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edma_setup_interrupt(struct edma_chan *echan, bool enable)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);

	if (enable) {
		edma_shadow0_write_array(ecc, SH_ICR, channel >> 5,
					 BIT(channel & 0x1f));
		edma_shadow0_write_array(ecc, SH_IESR, channel >> 5,
					 BIT(channel & 0x1f));
	} else {
		edma_shadow0_write_array(ecc, SH_IECR, channel >> 5,
					 BIT(channel & 0x1f));
	}
}