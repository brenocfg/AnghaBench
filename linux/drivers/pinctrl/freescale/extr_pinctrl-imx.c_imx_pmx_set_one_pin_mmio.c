#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct imx_pinctrl_soc_info {int flags; int mux_mask; int mux_shift; TYPE_2__* pins; } ;
struct imx_pinctrl {int base; int input_sel_base; int /*<<< orphan*/  dev; struct imx_pin_reg* pin_regs; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin_reg {int mux_reg; } ;
struct imx_pin_mmio {int mux_mode; int input_val; int input_reg; } ;
struct TYPE_3__ {struct imx_pin_mmio mmio; } ;
struct imx_pin {unsigned int pin; TYPE_1__ conf; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SHARE_MUX_CONF_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int imx_pmx_set_one_pin_mmio(struct imx_pinctrl *ipctl,
				    struct imx_pin *pin)
{
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	struct imx_pin_mmio *pin_mmio = &pin->conf.mmio;
	const struct imx_pin_reg *pin_reg;
	unsigned int pin_id;

	pin_id = pin->pin;
	pin_reg = &ipctl->pin_regs[pin_id];

	if (pin_reg->mux_reg == -1) {
		dev_dbg(ipctl->dev, "Pin(%s) does not support mux function\n",
			info->pins[pin_id].name);
		return 0;
	}

	if (info->flags & SHARE_MUX_CONF_REG) {
		u32 reg;

		reg = readl(ipctl->base + pin_reg->mux_reg);
		reg &= ~info->mux_mask;
		reg |= (pin_mmio->mux_mode << info->mux_shift);
		writel(reg, ipctl->base + pin_reg->mux_reg);
		dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
			pin_reg->mux_reg, reg);
	} else {
		writel(pin_mmio->mux_mode, ipctl->base + pin_reg->mux_reg);
		dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
			pin_reg->mux_reg, pin_mmio->mux_mode);
	}

	/*
	 * If the select input value begins with 0xff, it's a quirky
	 * select input and the value should be interpreted as below.
	 *     31     23      15      7        0
	 *     | 0xff | shift | width | select |
	 * It's used to work around the problem that the select
	 * input for some pin is not implemented in the select
	 * input register but in some general purpose register.
	 * We encode the select input value, width and shift of
	 * the bit field into input_val cell of pin function ID
	 * in device tree, and then decode them here for setting
	 * up the select input bits in general purpose register.
	 */
	if (pin_mmio->input_val >> 24 == 0xff) {
		u32 val = pin_mmio->input_val;
		u8 select = val & 0xff;
		u8 width = (val >> 8) & 0xff;
		u8 shift = (val >> 16) & 0xff;
		u32 mask = ((1 << width) - 1) << shift;
		/*
		 * The input_reg[i] here is actually some IOMUXC general
		 * purpose register, not regular select input register.
		 */
		val = readl(ipctl->base + pin_mmio->input_reg);
		val &= ~mask;
		val |= select << shift;
		writel(val, ipctl->base + pin_mmio->input_reg);
	} else if (pin_mmio->input_reg) {
		/*
		 * Regular select input register can never be at offset
		 * 0, and we only print register value for regular case.
		 */
		if (ipctl->input_sel_base)
			writel(pin_mmio->input_val, ipctl->input_sel_base +
					pin_mmio->input_reg);
		else
			writel(pin_mmio->input_val, ipctl->base +
					pin_mmio->input_reg);
		dev_dbg(ipctl->dev,
			"==>select_input: offset 0x%x val 0x%x\n",
			pin_mmio->input_reg, pin_mmio->input_val);
	}

	return 0;
}