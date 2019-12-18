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
struct isp1760_device {int devflags; int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; scalar_t__ rst_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_MODE ; 
 int /*<<< orphan*/  HC_HW_MODE_CTRL ; 
 int /*<<< orphan*/  HC_PORT1_CTRL ; 
 int /*<<< orphan*/  HC_RESET_REG ; 
 int HW_ANA_DIGI_OC ; 
 int HW_COMN_IRQ ; 
 int HW_DACK_POL_HIGH ; 
 int HW_DATA_BUS_32BIT ; 
 int HW_DM_PULLDOWN ; 
 int HW_DP_PULLDOWN ; 
 int HW_DREQ_POL_HIGH ; 
 int HW_INTR_EDGE_TRIG ; 
 int HW_INTR_HIGH_ACT ; 
 int HW_OTG_DISABLE ; 
 int HW_SEL_CP_EXT ; 
 int HW_SW_SEL_HC_DC ; 
 int HW_VBUS_DRV ; 
 int ISP1760_FLAG_ANALOG_OC ; 
 int ISP1760_FLAG_BUS_WIDTH_16 ; 
 int ISP1760_FLAG_DACK_POL_HIGH ; 
 int ISP1760_FLAG_DREQ_POL_HIGH ; 
 int ISP1760_FLAG_INTR_EDGE_TRIG ; 
 int ISP1760_FLAG_INTR_POL_HIGH ; 
 int ISP1760_FLAG_ISP1761 ; 
 int ISP1760_FLAG_OTG_EN ; 
 int SW_RESET_RESET_ALL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  isp1760_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void isp1760_init_core(struct isp1760_device *isp)
{
	u32 otgctrl;
	u32 hwmode;

	/* Low-level chip reset */
	if (isp->rst_gpio) {
		gpiod_set_value_cansleep(isp->rst_gpio, 1);
		msleep(50);
		gpiod_set_value_cansleep(isp->rst_gpio, 0);
	}

	/*
	 * Reset the host controller, including the CPU interface
	 * configuration.
	 */
	isp1760_write32(isp->regs, HC_RESET_REG, SW_RESET_RESET_ALL);
	msleep(100);

	/* Setup HW Mode Control: This assumes a level active-low interrupt */
	hwmode = HW_DATA_BUS_32BIT;

	if (isp->devflags & ISP1760_FLAG_BUS_WIDTH_16)
		hwmode &= ~HW_DATA_BUS_32BIT;
	if (isp->devflags & ISP1760_FLAG_ANALOG_OC)
		hwmode |= HW_ANA_DIGI_OC;
	if (isp->devflags & ISP1760_FLAG_DACK_POL_HIGH)
		hwmode |= HW_DACK_POL_HIGH;
	if (isp->devflags & ISP1760_FLAG_DREQ_POL_HIGH)
		hwmode |= HW_DREQ_POL_HIGH;
	if (isp->devflags & ISP1760_FLAG_INTR_POL_HIGH)
		hwmode |= HW_INTR_HIGH_ACT;
	if (isp->devflags & ISP1760_FLAG_INTR_EDGE_TRIG)
		hwmode |= HW_INTR_EDGE_TRIG;

	/*
	 * The ISP1761 has a dedicated DC IRQ line but supports sharing the HC
	 * IRQ line for both the host and device controllers. Hardcode IRQ
	 * sharing for now and disable the DC interrupts globally to avoid
	 * spurious interrupts during HCD registration.
	 */
	if (isp->devflags & ISP1760_FLAG_ISP1761) {
		isp1760_write32(isp->regs, DC_MODE, 0);
		hwmode |= HW_COMN_IRQ;
	}

	/*
	 * We have to set this first in case we're in 16-bit mode.
	 * Write it twice to ensure correct upper bits if switching
	 * to 16-bit mode.
	 */
	isp1760_write32(isp->regs, HC_HW_MODE_CTRL, hwmode);
	isp1760_write32(isp->regs, HC_HW_MODE_CTRL, hwmode);

	/*
	 * PORT 1 Control register of the ISP1760 is the OTG control register
	 * on ISP1761.
	 *
	 * TODO: Really support OTG. For now we configure port 1 in device mode
	 * when OTG is requested.
	 */
	if ((isp->devflags & ISP1760_FLAG_ISP1761) &&
	    (isp->devflags & ISP1760_FLAG_OTG_EN))
		otgctrl = ((HW_DM_PULLDOWN | HW_DP_PULLDOWN) << 16)
			| HW_OTG_DISABLE;
	else
		otgctrl = (HW_SW_SEL_HC_DC << 16)
			| (HW_VBUS_DRV | HW_SEL_CP_EXT);

	isp1760_write32(isp->regs, HC_PORT1_CTRL, otgctrl);

	dev_info(isp->dev, "bus width: %u, oc: %s\n",
		 isp->devflags & ISP1760_FLAG_BUS_WIDTH_16 ? 16 : 32,
		 isp->devflags & ISP1760_FLAG_ANALOG_OC ? "analog" : "digital");
}