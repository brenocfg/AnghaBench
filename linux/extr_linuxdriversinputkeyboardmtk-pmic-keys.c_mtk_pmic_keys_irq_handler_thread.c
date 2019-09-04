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
typedef  int u32 ;
struct mtk_pmic_keys_info {int /*<<< orphan*/  keycode; TYPE_1__* keys; TYPE_2__* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int deb_mask; int /*<<< orphan*/  deb_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t mtk_pmic_keys_irq_handler_thread(int irq, void *data)
{
	struct mtk_pmic_keys_info *info = data;
	u32 key_deb, pressed;

	regmap_read(info->keys->regmap, info->regs->deb_reg, &key_deb);

	key_deb &= info->regs->deb_mask;

	pressed = !key_deb;

	input_report_key(info->keys->input_dev, info->keycode, pressed);
	input_sync(info->keys->input_dev);

	dev_dbg(info->keys->dev, "(%s) key =%d using PMIC\n",
		 pressed ? "pressed" : "released", info->keycode);

	return IRQ_HANDLED;
}