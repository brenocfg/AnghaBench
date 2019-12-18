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
typedef  size_t u8 ;
struct stmpe_gpio {struct stmpe* stmpe; } ;
struct stmpe {size_t* regs; int partnum; } ;
struct seq_file {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 size_t BIT (unsigned int) ; 
 size_t NOT_SUPPORTED_IDX ; 
#define  STMPE1600 135 
#define  STMPE1601 134 
#define  STMPE1801 133 
#define  STMPE2401 132 
#define  STMPE2403 131 
#define  STMPE610 130 
#define  STMPE801 129 
#define  STMPE811 128 
 size_t STMPE_IDX_GPDR_LSB ; 
 int /*<<< orphan*/  STMPE_IDX_GPEDR_LSB ; 
 int /*<<< orphan*/  STMPE_IDX_GPFER_LSB ; 
 int /*<<< orphan*/  STMPE_IDX_GPRER_LSB ; 
 int /*<<< orphan*/  STMPE_IDX_IEGPIOR_LSB ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 char* gpiochip_is_requested (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,char*,char*,...) ; 
 int /*<<< orphan*/  stmpe_gpio_get (struct gpio_chip*,unsigned int) ; 
 int stmpe_reg_read (struct stmpe*,size_t) ; 

__attribute__((used)) static void stmpe_dbg_show_one(struct seq_file *s,
			       struct gpio_chip *gc,
			       unsigned offset, unsigned gpio)
{
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(gc);
	struct stmpe *stmpe = stmpe_gpio->stmpe;
	const char *label = gpiochip_is_requested(gc, offset);
	bool val = !!stmpe_gpio_get(gc, offset);
	u8 bank = offset / 8;
	u8 dir_reg = stmpe->regs[STMPE_IDX_GPDR_LSB + bank];
	u8 mask = BIT(offset % 8);
	int ret;
	u8 dir;

	ret = stmpe_reg_read(stmpe, dir_reg);
	if (ret < 0)
		return;
	dir = !!(ret & mask);

	if (dir) {
		seq_printf(s, " gpio-%-3d (%-20.20s) out %s",
			   gpio, label ?: "(none)",
			   val ? "hi" : "lo");
	} else {
		u8 edge_det_reg;
		u8 rise_reg;
		u8 fall_reg;
		u8 irqen_reg;

		static const char * const edge_det_values[] = {
			"edge-inactive",
			"edge-asserted",
			"not-supported"
		};
		static const char * const rise_values[] = {
			"no-rising-edge-detection",
			"rising-edge-detection",
			"not-supported"
		};
		static const char * const fall_values[] = {
			"no-falling-edge-detection",
			"falling-edge-detection",
			"not-supported"
		};
		#define NOT_SUPPORTED_IDX 2
		u8 edge_det = NOT_SUPPORTED_IDX;
		u8 rise = NOT_SUPPORTED_IDX;
		u8 fall = NOT_SUPPORTED_IDX;
		bool irqen;

		switch (stmpe->partnum) {
		case STMPE610:
		case STMPE811:
		case STMPE1601:
		case STMPE2401:
		case STMPE2403:
			edge_det_reg = stmpe->regs[STMPE_IDX_GPEDR_LSB + bank];
			ret = stmpe_reg_read(stmpe, edge_det_reg);
			if (ret < 0)
				return;
			edge_det = !!(ret & mask);
			/* fall through */
		case STMPE1801:
			rise_reg = stmpe->regs[STMPE_IDX_GPRER_LSB + bank];
			fall_reg = stmpe->regs[STMPE_IDX_GPFER_LSB + bank];

			ret = stmpe_reg_read(stmpe, rise_reg);
			if (ret < 0)
				return;
			rise = !!(ret & mask);
			ret = stmpe_reg_read(stmpe, fall_reg);
			if (ret < 0)
				return;
			fall = !!(ret & mask);
			/* fall through */
		case STMPE801:
		case STMPE1600:
			irqen_reg = stmpe->regs[STMPE_IDX_IEGPIOR_LSB + bank];
			break;

		default:
			return;
		}

		ret = stmpe_reg_read(stmpe, irqen_reg);
		if (ret < 0)
			return;
		irqen = !!(ret & mask);

		seq_printf(s, " gpio-%-3d (%-20.20s) in  %s %13s %13s %25s %25s",
			   gpio, label ?: "(none)",
			   val ? "hi" : "lo",
			   edge_det_values[edge_det],
			   irqen ? "IRQ-enabled" : "IRQ-disabled",
			   rise_values[rise],
			   fall_values[fall]);
	}
}