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
struct hdmi_pll_8996 {scalar_t__ mmio_qserdes_com; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 hdmi_pll_read(struct hdmi_pll_8996 *pll, int offset)
{
	return msm_readl(pll->mmio_qserdes_com + offset);
}