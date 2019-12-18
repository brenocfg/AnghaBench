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
struct img_ir_priv_hw {int /*<<< orphan*/ * ct_quirks; } ;
struct img_ir_priv {struct img_ir_priv_hw hw; } ;

/* Variables and functions */
 size_t IMG_IR_CODETYPE_2BITPULSEPOS ; 
 size_t IMG_IR_CODETYPE_BIPHASE ; 
 size_t IMG_IR_CODETYPE_PULSELEN ; 
 int /*<<< orphan*/  IMG_IR_QUIRK_CODE_BROKEN ; 
 int /*<<< orphan*/  IMG_IR_QUIRK_CODE_IRQ ; 
 int /*<<< orphan*/  IMG_IR_QUIRK_CODE_LEN_INCR ; 

__attribute__((used)) static void img_ir_probe_hw_caps(struct img_ir_priv *priv)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	/*
	 * When a version of the block becomes available without these quirks,
	 * they'll have to depend on the core revision.
	 */
	hw->ct_quirks[IMG_IR_CODETYPE_PULSELEN]
		|= IMG_IR_QUIRK_CODE_LEN_INCR;
	hw->ct_quirks[IMG_IR_CODETYPE_BIPHASE]
		|= IMG_IR_QUIRK_CODE_IRQ;
	hw->ct_quirks[IMG_IR_CODETYPE_2BITPULSEPOS]
		|= IMG_IR_QUIRK_CODE_BROKEN;
}