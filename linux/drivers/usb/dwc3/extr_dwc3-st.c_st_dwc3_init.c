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
struct st_dwc3 {int /*<<< orphan*/  glue_base; } ;

/* Variables and functions */
 int AUX_CLK_EN ; 
 int /*<<< orphan*/  CLKRST_CTRL ; 
 int EXT_CFG_RESET_N ; 
 int SEL_OVERRIDE_BVALID (int /*<<< orphan*/ ) ; 
 int SEL_OVERRIDE_POWERPRESENT (int /*<<< orphan*/ ) ; 
 int SEL_OVERRIDE_VBUSVALID (int /*<<< orphan*/ ) ; 
 int SW_PIPEW_RESET_N ; 
 int /*<<< orphan*/  USB2_VBUS_MNGMNT_SEL1 ; 
 int /*<<< orphan*/  USB2_VBUS_UTMIOTG ; 
 int XHCI_REVISION ; 
 int st_dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void st_dwc3_init(struct st_dwc3 *dwc3_data)
{
	u32 reg = st_dwc3_readl(dwc3_data->glue_base, CLKRST_CTRL);

	reg |= AUX_CLK_EN | EXT_CFG_RESET_N | XHCI_REVISION;
	reg &= ~SW_PIPEW_RESET_N;
	st_dwc3_writel(dwc3_data->glue_base, CLKRST_CTRL, reg);

	/* configure mux for vbus, powerpresent and bvalid signals */
	reg = st_dwc3_readl(dwc3_data->glue_base, USB2_VBUS_MNGMNT_SEL1);

	reg |= SEL_OVERRIDE_VBUSVALID(USB2_VBUS_UTMIOTG) |
		SEL_OVERRIDE_POWERPRESENT(USB2_VBUS_UTMIOTG) |
		SEL_OVERRIDE_BVALID(USB2_VBUS_UTMIOTG);

	st_dwc3_writel(dwc3_data->glue_base, USB2_VBUS_MNGMNT_SEL1, reg);

	reg = st_dwc3_readl(dwc3_data->glue_base, CLKRST_CTRL);
	reg |= SW_PIPEW_RESET_N;
	st_dwc3_writel(dwc3_data->glue_base, CLKRST_CTRL, reg);
}