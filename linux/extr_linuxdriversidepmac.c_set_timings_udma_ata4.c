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
typedef  int u8 ;
typedef  unsigned int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addrSetup; int /*<<< orphan*/  wrDataSetup; int /*<<< orphan*/  rdy2pause; } ;

/* Variables and functions */
 unsigned int SYSCLK_TICKS_66 (int /*<<< orphan*/ ) ; 
 unsigned int TR_66_MDMA_MASK ; 
 unsigned int TR_66_UDMA_ADDRSETUP_SHIFT ; 
 unsigned int TR_66_UDMA_EN ; 
 unsigned int TR_66_UDMA_MASK ; 
 unsigned int TR_66_UDMA_RDY2PAUS_SHIFT ; 
 unsigned int TR_66_UDMA_WRDATASETUP_SHIFT ; 
 int XFER_UDMA_4 ; 
 TYPE_1__* kl66_udma_timings ; 

__attribute__((used)) static int
set_timings_udma_ata4(u32 *timings, u8 speed)
{
	unsigned rdyToPauseTicks, wrDataSetupTicks, addrTicks;

	if (speed > XFER_UDMA_4)
		return 1;

	rdyToPauseTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].rdy2pause);
	wrDataSetupTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].wrDataSetup);
	addrTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].addrSetup);

	*timings = ((*timings) & ~(TR_66_UDMA_MASK | TR_66_MDMA_MASK)) |
			(wrDataSetupTicks << TR_66_UDMA_WRDATASETUP_SHIFT) | 
			(rdyToPauseTicks << TR_66_UDMA_RDY2PAUS_SHIFT) |
			(addrTicks <<TR_66_UDMA_ADDRSETUP_SHIFT) |
			TR_66_UDMA_EN;
#ifdef IDE_PMAC_DEBUG
	printk(KERN_ERR "ide_pmac: Set UDMA timing for mode %d, reg: 0x%08x\n",
		speed & 0xf,  *timings);
#endif	

	return 0;
}