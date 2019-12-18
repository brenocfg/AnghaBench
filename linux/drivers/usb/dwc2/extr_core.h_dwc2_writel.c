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
struct dwc2_hsotg {scalar_t__ regs; scalar_t__ needs_byte_swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ swab32 (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void dwc2_writel(struct dwc2_hsotg *hsotg, u32 value, u32 offset)
{
	if (hsotg->needs_byte_swap)
		writel(swab32(value), hsotg->regs + offset);
	else
		writel(value, hsotg->regs + offset);

#ifdef DWC2_LOG_WRITES
	pr_info("info:: wrote %08x to %p\n", value, hsotg->regs + offset);
#endif
}