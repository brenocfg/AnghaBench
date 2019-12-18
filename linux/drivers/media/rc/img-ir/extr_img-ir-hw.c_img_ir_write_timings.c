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
struct img_ir_timing_regvals {int /*<<< orphan*/  s11; int /*<<< orphan*/  s10; int /*<<< orphan*/  s01; int /*<<< orphan*/  s00; int /*<<< orphan*/  ldr; int /*<<< orphan*/  ft; } ;
struct img_ir_priv_hw {int flags; int /*<<< orphan*/ * filters; } ;
struct img_ir_priv {int /*<<< orphan*/  dev; struct img_ir_priv_hw hw; } ;
typedef  enum rc_filter_type { ____Placeholder_rc_filter_type } rc_filter_type ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IMG_IR_FREE_SYMB_TIMING ; 
 int /*<<< orphan*/  IMG_IR_LEAD_SYMB_TIMING ; 
 int /*<<< orphan*/  IMG_IR_S00_SYMB_TIMING ; 
 int /*<<< orphan*/  IMG_IR_S01_SYMB_TIMING ; 
 int /*<<< orphan*/  IMG_IR_S10_SYMB_TIMING ; 
 int /*<<< orphan*/  IMG_IR_S11_SYMB_TIMING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_free_timing_dynamic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_ir_write_timings(struct img_ir_priv *priv,
				 struct img_ir_timing_regvals *regs,
				 enum rc_filter_type type)
{
	struct img_ir_priv_hw *hw = &priv->hw;

	/* filter may be more restrictive to minlen, maxlen */
	u32 ft = regs->ft;
	if (hw->flags & BIT(type))
		ft = img_ir_free_timing_dynamic(regs->ft, &hw->filters[type]);
	/* write to registers */
	img_ir_write(priv, IMG_IR_LEAD_SYMB_TIMING, regs->ldr);
	img_ir_write(priv, IMG_IR_S00_SYMB_TIMING, regs->s00);
	img_ir_write(priv, IMG_IR_S01_SYMB_TIMING, regs->s01);
	img_ir_write(priv, IMG_IR_S10_SYMB_TIMING, regs->s10);
	img_ir_write(priv, IMG_IR_S11_SYMB_TIMING, regs->s11);
	img_ir_write(priv, IMG_IR_FREE_SYMB_TIMING, ft);
	dev_dbg(priv->dev, "timings: ldr=%#x, s=[%#x, %#x, %#x, %#x], ft=%#x\n",
		regs->ldr, regs->s00, regs->s01, regs->s10, regs->s11, ft);
}