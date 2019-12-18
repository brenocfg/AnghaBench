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
typedef  int u16 ;
struct zx_pinctrl_soc_info {struct pinctrl_pin_desc* pins; } ;
struct zx_pinctrl {int aux_base; int base; int /*<<< orphan*/  lock; struct zx_pinctrl_soc_info* info; } ;
struct zx_pin_data {int width; int offset; int bitpos; scalar_t__ aon_pin; struct zx_mux_desc* muxes; } ;
struct zx_mux_desc {int muxval; scalar_t__ name; } ;
struct pinctrl_pin_desc {int number; struct zx_pin_data* drv_data; } ;
struct pinctrl_dev {int dummy; } ;
struct function_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AON_MUX_FLAG ; 
 int EINVAL ; 
 int NONAON_MVAL ; 
 struct zx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct function_desc* pinmux_generic_get_function (struct pinctrl_dev*,unsigned int) ; 
 int readl (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int zx_set_mux(struct pinctrl_dev *pctldev, unsigned int func_selector,
		      unsigned int group_selector)
{
	struct zx_pinctrl *zpctl = pinctrl_dev_get_drvdata(pctldev);
	struct zx_pinctrl_soc_info *info = zpctl->info;
	const struct pinctrl_pin_desc *pindesc = info->pins + group_selector;
	struct zx_pin_data *data = pindesc->drv_data;
	struct zx_mux_desc *mux;
	u32 mask, offset, bitpos;
	struct function_desc *func;
	unsigned long flags;
	u32 val, mval;

	/* Skip reserved pin */
	if (!data)
		return -EINVAL;

	mux = data->muxes;
	mask = (1 << data->width) - 1;
	offset = data->offset;
	bitpos = data->bitpos;

	func = pinmux_generic_get_function(pctldev, func_selector);
	if (!func)
		return -EINVAL;

	while (mux->name) {
		if (strcmp(mux->name, func->name) == 0)
			break;
		mux++;
	}

	/* Found mux value to be written */
	mval = mux->muxval;

	spin_lock_irqsave(&zpctl->lock, flags);

	if (data->aon_pin) {
		/*
		 * It's an AON pin, whose mux register offset and bit position
		 * can be caluculated from pin number.  Each register covers 16
		 * pins, and each pin occupies 2 bits.
		 */
		u16 aoffset = pindesc->number / 16 * 4;
		u16 abitpos = (pindesc->number % 16) * 2;

		if (mval & AON_MUX_FLAG) {
			/*
			 * This is a mux value that needs to be written into
			 * AON pinmux register.  Write it and then we're done.
			 */
			val = readl(zpctl->aux_base + aoffset);
			val &= ~(0x3 << abitpos);
			val |= (mval & 0x3) << abitpos;
			writel(val, zpctl->aux_base + aoffset);
		} else {
			/*
			 * It's a mux value that needs to be written into TOP
			 * pinmux register.
			 */
			val = readl(zpctl->base + offset);
			val &= ~(mask << bitpos);
			val |= (mval & mask) << bitpos;
			writel(val, zpctl->base + offset);

			/*
			 * In this case, the AON pinmux register needs to be
			 * set up to select non-AON function.
			 */
			val = readl(zpctl->aux_base + aoffset);
			val &= ~(0x3 << abitpos);
			val |= NONAON_MVAL << abitpos;
			writel(val, zpctl->aux_base + aoffset);
		}

	} else {
		/*
		 * This is a TOP pin, and we only need to set up TOP pinmux
		 * register and then we're done with it.
		 */
		val = readl(zpctl->base + offset);
		val &= ~(mask << bitpos);
		val |= (mval & mask) << bitpos;
		writel(val, zpctl->base + offset);
	}

	spin_unlock_irqrestore(&zpctl->lock, flags);

	return 0;
}