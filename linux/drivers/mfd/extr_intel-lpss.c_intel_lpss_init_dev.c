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
typedef  int /*<<< orphan*/  u32 ;
struct intel_lpss {scalar_t__ type; scalar_t__ priv; } ;

/* Variables and functions */
 scalar_t__ LPSS_DEV_SPI ; 
 scalar_t__ LPSS_PRIV_RESETS ; 
 scalar_t__ LPSS_PRIV_SSP_REG ; 
 int /*<<< orphan*/  LPSS_PRIV_SSP_REG_DIS_DMA_FIN ; 
 int /*<<< orphan*/  intel_lpss_deassert_reset (struct intel_lpss const*) ; 
 int /*<<< orphan*/  intel_lpss_has_idma (struct intel_lpss const*) ; 
 int /*<<< orphan*/  intel_lpss_set_remap_addr (struct intel_lpss const*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_lpss_init_dev(const struct intel_lpss *lpss)
{
	u32 value = LPSS_PRIV_SSP_REG_DIS_DMA_FIN;

	/* Set the device in reset state */
	writel(0, lpss->priv + LPSS_PRIV_RESETS);

	intel_lpss_deassert_reset(lpss);

	intel_lpss_set_remap_addr(lpss);

	if (!intel_lpss_has_idma(lpss))
		return;

	/* Make sure that SPI multiblock DMA transfers are re-enabled */
	if (lpss->type == LPSS_DEV_SPI)
		writel(value, lpss->priv + LPSS_PRIV_SSP_REG);
}