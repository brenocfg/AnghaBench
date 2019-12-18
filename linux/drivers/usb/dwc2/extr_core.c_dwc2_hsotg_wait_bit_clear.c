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
typedef  scalar_t__ u32 ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ dwc2_readl (struct dwc2_hsotg*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

int dwc2_hsotg_wait_bit_clear(struct dwc2_hsotg *hsotg, u32 offset, u32 mask,
			      u32 timeout)
{
	u32 i;

	for (i = 0; i < timeout; i++) {
		if (!(dwc2_readl(hsotg, offset) & mask))
			return 0;
		udelay(1);
	}

	return -ETIMEDOUT;
}