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
struct pti_device {int patgen; int mode; int clkdiv; int lpp_dest; scalar_t__ base; scalar_t__ freeclk; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPP_DEST ; 
 int /*<<< orphan*/  PTI_CLKDIV ; 
 int PTI_EN ; 
 int PTI_FCEN ; 
 int /*<<< orphan*/  PTI_MODE ; 
 int /*<<< orphan*/  PTI_PATGENMODE ; 
 scalar_t__ REG_PTI_CTL ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 struct pti_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_trace_enable (struct intel_th_device*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static int intel_th_pti_activate(struct intel_th_device *thdev)
{
	struct pti_device *pti = dev_get_drvdata(&thdev->dev);
	u32 ctl = PTI_EN;

	if (pti->patgen)
		ctl |= pti->patgen << __ffs(PTI_PATGENMODE);
	if (pti->freeclk)
		ctl |= PTI_FCEN;
	ctl |= pti->mode << __ffs(PTI_MODE);
	ctl |= pti->clkdiv << __ffs(PTI_CLKDIV);
	ctl |= pti->lpp_dest << __ffs(LPP_DEST);

	iowrite32(ctl, pti->base + REG_PTI_CTL);

	intel_th_trace_enable(thdev);

	return 0;
}