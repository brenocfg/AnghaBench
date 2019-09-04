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
struct solo_p2m_dev {int /*<<< orphan*/  completion; int /*<<< orphan*/  mutex; } ;
struct solo_dev {int sdram_size; int sys_config; TYPE_1__* pdev; struct solo_p2m_dev* p2m_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SOLO_DMA_CTRL ; 
 int SOLO_DMA_CTRL_LATENCY (int) ; 
 int SOLO_DMA_CTRL_READ_CLK_SELECT ; 
 int SOLO_DMA_CTRL_REFRESH_CYCLE (int) ; 
 int SOLO_DMA_CTRL_SDRAM_CLK_INVERT ; 
 int SOLO_DMA_CTRL_SDRAM_SIZE (int) ; 
 int /*<<< orphan*/  SOLO_IRQ_P2M (int) ; 
 int SOLO_NR_P2M ; 
 int /*<<< orphan*/  SOLO_P2M_CONFIG (int) ; 
 int /*<<< orphan*/  SOLO_P2M_CONTROL (int) ; 
 int SOLO_P2M_CSC_16BIT_565 ; 
 int SOLO_P2M_DESC_INTR_OPT ; 
 int SOLO_P2M_DMA_INTERVAL (int /*<<< orphan*/ ) ; 
 int SOLO_P2M_PCI_MASTER_MODE ; 
 int SOLO_SDRAM_END (struct solo_dev*) ; 
 int /*<<< orphan*/  SOLO_SYS_CFG ; 
 int SOLO_SYS_CFG_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_irq_on (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_p2m_test (struct solo_dev*,int,int) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

int solo_p2m_init(struct solo_dev *solo_dev)
{
	struct solo_p2m_dev *p2m_dev;
	int i;

	for (i = 0; i < SOLO_NR_P2M; i++) {
		p2m_dev = &solo_dev->p2m_dev[i];

		mutex_init(&p2m_dev->mutex);
		init_completion(&p2m_dev->completion);

		solo_reg_write(solo_dev, SOLO_P2M_CONTROL(i), 0);
		solo_reg_write(solo_dev, SOLO_P2M_CONFIG(i),
			       SOLO_P2M_CSC_16BIT_565 |
			       SOLO_P2M_DESC_INTR_OPT |
			       SOLO_P2M_DMA_INTERVAL(0) |
			       SOLO_P2M_PCI_MASTER_MODE);
		solo_irq_on(solo_dev, SOLO_IRQ_P2M(i));
	}

	/* Find correct SDRAM size */
	for (solo_dev->sdram_size = 0, i = 2; i >= 0; i--) {
		solo_reg_write(solo_dev, SOLO_DMA_CTRL,
			       SOLO_DMA_CTRL_REFRESH_CYCLE(1) |
			       SOLO_DMA_CTRL_SDRAM_SIZE(i) |
			       SOLO_DMA_CTRL_SDRAM_CLK_INVERT |
			       SOLO_DMA_CTRL_READ_CLK_SELECT |
			       SOLO_DMA_CTRL_LATENCY(1));

		solo_reg_write(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config |
			       SOLO_SYS_CFG_RESET);
		solo_reg_write(solo_dev, SOLO_SYS_CFG, solo_dev->sys_config);

		switch (i) {
		case 2:
			if (solo_p2m_test(solo_dev, 0x07ff0000, 0x00010000) ||
			    solo_p2m_test(solo_dev, 0x05ff0000, 0x00010000))
				continue;
			break;

		case 1:
			if (solo_p2m_test(solo_dev, 0x03ff0000, 0x00010000))
				continue;
			break;

		default:
			if (solo_p2m_test(solo_dev, 0x01ff0000, 0x00010000))
				continue;
		}

		solo_dev->sdram_size = (32 << 20) << i;
		break;
	}

	if (!solo_dev->sdram_size) {
		dev_err(&solo_dev->pdev->dev, "Error detecting SDRAM size\n");
		return -EIO;
	}

	if (SOLO_SDRAM_END(solo_dev) > solo_dev->sdram_size) {
		dev_err(&solo_dev->pdev->dev,
			"SDRAM is not large enough (%u < %u)\n",
			solo_dev->sdram_size, SOLO_SDRAM_END(solo_dev));
		return -EIO;
	}

	return 0;
}