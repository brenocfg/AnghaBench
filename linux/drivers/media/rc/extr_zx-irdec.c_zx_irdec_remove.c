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
struct zx_irdec {scalar_t__ base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZX_IREN ; 
 int /*<<< orphan*/  ZX_IR_ENABLE ; 
 scalar_t__ ZX_IR_INTEN ; 
 struct zx_irdec* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zx_irdec_set_mask (struct zx_irdec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_irdec_remove(struct platform_device *pdev)
{
	struct zx_irdec *irdec = platform_get_drvdata(pdev);

	/* Disable the decoder */
	zx_irdec_set_mask(irdec, ZX_IR_ENABLE, ZX_IREN, 0);

	/* Disable interrupt */
	writel(0, irdec->base + ZX_IR_INTEN);

	return 0;
}