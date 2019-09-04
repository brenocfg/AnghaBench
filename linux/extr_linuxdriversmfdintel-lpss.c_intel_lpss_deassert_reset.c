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
struct intel_lpss {scalar_t__ priv; } ;

/* Variables and functions */
 scalar_t__ LPSS_PRIV_RESETS ; 
 int LPSS_PRIV_RESETS_FUNC ; 
 int LPSS_PRIV_RESETS_IDMA ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void intel_lpss_deassert_reset(const struct intel_lpss *lpss)
{
	u32 value = LPSS_PRIV_RESETS_FUNC | LPSS_PRIV_RESETS_IDMA;

	/* Bring out the device from reset */
	writel(value, lpss->priv + LPSS_PRIV_RESETS);
}