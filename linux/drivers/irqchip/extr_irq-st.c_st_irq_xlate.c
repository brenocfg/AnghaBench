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
struct st_irq_syscfg {int /*<<< orphan*/  config; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ST_A9_FIQ_N_SEL (int,int) ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_CTI_0 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_CTI_1 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_EXT_0 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_EXT_1 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_EXT_2 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_PL310_L2 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_PMU_0 ; 
 int /*<<< orphan*/  ST_A9_IRQ_EN_PMU_1 ; 
 int /*<<< orphan*/  ST_A9_IRQ_N_SEL (int,int) ; 
#define  ST_IRQ_SYSCFG_CTI_0 136 
#define  ST_IRQ_SYSCFG_CTI_1 135 
#define  ST_IRQ_SYSCFG_DISABLED 134 
#define  ST_IRQ_SYSCFG_EXT_0 133 
#define  ST_IRQ_SYSCFG_EXT_1 132 
#define  ST_IRQ_SYSCFG_EXT_2 131 
#define  ST_IRQ_SYSCFG_PMU_0 130 
#define  ST_IRQ_SYSCFG_PMU_1 129 
#define  ST_IRQ_SYSCFG_pl310_L2 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct st_irq_syscfg* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_irq_xlate(struct platform_device *pdev,
			int device, int channel, bool irq)
{
	struct st_irq_syscfg *ddata = dev_get_drvdata(&pdev->dev);

	/* Set the device enable bit. */
	switch (device) {
	case ST_IRQ_SYSCFG_EXT_0:
		ddata->config |= ST_A9_IRQ_EN_EXT_0;
		break;
	case ST_IRQ_SYSCFG_EXT_1:
		ddata->config |= ST_A9_IRQ_EN_EXT_1;
		break;
	case ST_IRQ_SYSCFG_EXT_2:
		ddata->config |= ST_A9_IRQ_EN_EXT_2;
		break;
	case ST_IRQ_SYSCFG_CTI_0:
		ddata->config |= ST_A9_IRQ_EN_CTI_0;
		break;
	case ST_IRQ_SYSCFG_CTI_1:
		ddata->config |= ST_A9_IRQ_EN_CTI_1;
		break;
	case ST_IRQ_SYSCFG_PMU_0:
		ddata->config |= ST_A9_IRQ_EN_PMU_0;
		break;
	case ST_IRQ_SYSCFG_PMU_1:
		ddata->config |= ST_A9_IRQ_EN_PMU_1;
		break;
	case ST_IRQ_SYSCFG_pl310_L2:
		ddata->config |= ST_A9_IRQ_EN_PL310_L2;
		break;
	case ST_IRQ_SYSCFG_DISABLED:
		return 0;
	default:
		dev_err(&pdev->dev, "Unrecognised device %d\n", device);
		return -EINVAL;
	}

	/* Select IRQ/FIQ channel for device. */
	ddata->config |= irq ?
		ST_A9_IRQ_N_SEL(device, channel) :
		ST_A9_FIQ_N_SEL(device, channel);

	return 0;
}