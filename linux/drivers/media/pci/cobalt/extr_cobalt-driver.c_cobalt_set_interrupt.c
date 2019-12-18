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
struct cobalt {scalar_t__ have_hsma_tx; scalar_t__ have_hsma_rx; } ;

/* Variables and functions */
 unsigned int COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VI0_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VI0_INT2_MSK ; 
 unsigned int COBALT_SYSSTAT_VI0_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VI1_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VI1_INT2_MSK ; 
 unsigned int COBALT_SYSSTAT_VI1_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VI2_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VI2_INT2_MSK ; 
 unsigned int COBALT_SYSSTAT_VI2_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VI3_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VI3_INT2_MSK ; 
 unsigned int COBALT_SYSSTAT_VI3_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VIHSMA_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VIHSMA_INT2_MSK ; 
 unsigned int COBALT_SYSSTAT_VIHSMA_LOST_DATA_MSK ; 
 unsigned int COBALT_SYSSTAT_VOHSMA_INT1_MSK ; 
 unsigned int COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK ; 
 int /*<<< orphan*/  COBALT_SYS_STAT_EDGE ; 
 int /*<<< orphan*/  COBALT_SYS_STAT_MASK ; 
 int /*<<< orphan*/  cobalt_write_bar1 (struct cobalt*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cobalt_set_interrupt(struct cobalt *cobalt, bool enable)
{
	if (enable) {
		unsigned irqs = COBALT_SYSSTAT_VI0_INT1_MSK |
				COBALT_SYSSTAT_VI1_INT1_MSK |
				COBALT_SYSSTAT_VI2_INT1_MSK |
				COBALT_SYSSTAT_VI3_INT1_MSK |
				COBALT_SYSSTAT_VI0_INT2_MSK |
				COBALT_SYSSTAT_VI1_INT2_MSK |
				COBALT_SYSSTAT_VI2_INT2_MSK |
				COBALT_SYSSTAT_VI3_INT2_MSK |
				COBALT_SYSSTAT_VI0_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI1_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI2_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI3_LOST_DATA_MSK |
				COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK;

		if (cobalt->have_hsma_rx)
			irqs |= COBALT_SYSSTAT_VIHSMA_INT1_MSK |
				COBALT_SYSSTAT_VIHSMA_INT2_MSK |
				COBALT_SYSSTAT_VIHSMA_LOST_DATA_MSK;

		if (cobalt->have_hsma_tx)
			irqs |= COBALT_SYSSTAT_VOHSMA_INT1_MSK |
				COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK |
				COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK;
		/* Clear any existing interrupts */
		cobalt_write_bar1(cobalt, COBALT_SYS_STAT_EDGE, 0xffffffff);
		/* PIO Core interrupt mask register.
		   Enable ADV7604 INT1 interrupts */
		cobalt_write_bar1(cobalt, COBALT_SYS_STAT_MASK, irqs);
	} else {
		/* Disable all ADV7604 interrupts */
		cobalt_write_bar1(cobalt, COBALT_SYS_STAT_MASK, 0);
	}
}