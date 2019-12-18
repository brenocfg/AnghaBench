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
typedef  int u32 ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSTS ; 
 int DSTS_SOFFN_MASK ; 
 int DSTS_SOFFN_SHIFT ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dwc2_hsotg_read_frameno(struct dwc2_hsotg *hsotg)
{
	u32 dsts;

	dsts = dwc2_readl(hsotg, DSTS);
	dsts &= DSTS_SOFFN_MASK;
	dsts >>= DSTS_SOFFN_SHIFT;

	return dsts;
}