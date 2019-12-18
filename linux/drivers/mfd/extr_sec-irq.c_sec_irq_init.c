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
struct sec_pmic_dev {int device_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_data; scalar_t__ irq_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap_pmic; } ;
struct regmap_irq_chip {int dummy; } ;
typedef  enum s2mps14_irq { ____Placeholder_s2mps14_irq } s2mps14_irq ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
#define  S2MPA01 135 
#define  S2MPS11X 134 
 scalar_t__ S2MPS11_IRQ_RTCA0 ; 
#define  S2MPS13X 133 
#define  S2MPS14X 132 
 int S2MPS14_IRQ_RTCA0 ; 
#define  S2MPS15X 131 
#define  S2MPU02 130 
#define  S5M8763X 129 
#define  S5M8767X 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,struct regmap_irq_chip const*,int /*<<< orphan*/ *) ; 
 struct regmap_irq_chip s2mps11_irq_chip ; 
 struct regmap_irq_chip s2mps13_irq_chip ; 
 struct regmap_irq_chip s2mps14_irq_chip ; 
 struct regmap_irq_chip s2mps15_irq_chip ; 
 struct regmap_irq_chip s2mpu02_irq_chip ; 
 struct regmap_irq_chip s5m8763_irq_chip ; 
 struct regmap_irq_chip s5m8767_irq_chip ; 

int sec_irq_init(struct sec_pmic_dev *sec_pmic)
{
	int ret = 0;
	int type = sec_pmic->device_type;
	const struct regmap_irq_chip *sec_irq_chip;

	if (!sec_pmic->irq) {
		dev_warn(sec_pmic->dev,
			 "No interrupt specified, no interrupts\n");
		sec_pmic->irq_base = 0;
		return 0;
	}

	switch (type) {
	case S5M8763X:
		sec_irq_chip = &s5m8763_irq_chip;
		break;
	case S5M8767X:
		sec_irq_chip = &s5m8767_irq_chip;
		break;
	case S2MPA01:
		sec_irq_chip = &s2mps14_irq_chip;
		break;
	case S2MPS11X:
		sec_irq_chip = &s2mps11_irq_chip;
		break;
	case S2MPS13X:
		sec_irq_chip = &s2mps13_irq_chip;
		break;
	case S2MPS14X:
		sec_irq_chip = &s2mps14_irq_chip;
		break;
	case S2MPS15X:
		sec_irq_chip = &s2mps15_irq_chip;
		break;
	case S2MPU02:
		sec_irq_chip = &s2mpu02_irq_chip;
		break;
	default:
		dev_err(sec_pmic->dev, "Unknown device type %lu\n",
			sec_pmic->device_type);
		return -EINVAL;
	}

	ret = devm_regmap_add_irq_chip(sec_pmic->dev, sec_pmic->regmap_pmic,
				       sec_pmic->irq,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       sec_pmic->irq_base, sec_irq_chip,
				       &sec_pmic->irq_data);
	if (ret != 0) {
		dev_err(sec_pmic->dev, "Failed to register IRQ chip: %d\n", ret);
		return ret;
	}

	/*
	 * The rtc-s5m driver requests S2MPS14_IRQ_RTCA0 also for S2MPS11
	 * so the interrupt number must be consistent.
	 */
	BUILD_BUG_ON(((enum s2mps14_irq)S2MPS11_IRQ_RTCA0) != S2MPS14_IRQ_RTCA0);

	return 0;
}