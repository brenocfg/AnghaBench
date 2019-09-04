#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_pmic_keys_info {int /*<<< orphan*/  keycode; int /*<<< orphan*/  irq; TYPE_1__* regs; struct mtk_pmic_keys* keys; } ;
struct mtk_pmic_keys {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  intsel_mask; int /*<<< orphan*/  intsel_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct mtk_pmic_keys_info*) ; 
 int /*<<< orphan*/  input_set_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pmic_keys_irq_handler_thread ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_pmic_key_setup(struct mtk_pmic_keys *keys,
		struct mtk_pmic_keys_info *info)
{
	int ret;

	info->keys = keys;

	ret = regmap_update_bits(keys->regmap, info->regs->intsel_reg,
				 info->regs->intsel_mask,
				 info->regs->intsel_mask);
	if (ret < 0)
		return ret;

	ret = devm_request_threaded_irq(keys->dev, info->irq, NULL,
					mtk_pmic_keys_irq_handler_thread,
					IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
					"mtk-pmic-keys", info);
	if (ret) {
		dev_err(keys->dev, "Failed to request IRQ: %d: %d\n",
			info->irq, ret);
		return ret;
	}

	input_set_capability(keys->input_dev, EV_KEY, info->keycode);

	return 0;
}