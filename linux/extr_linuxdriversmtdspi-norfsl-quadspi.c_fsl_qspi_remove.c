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
struct platform_device {int dummy; } ;
struct fsl_qspi {int nor_num; scalar_t__ ahb_addr; int /*<<< orphan*/  lock; scalar_t__ iobase; TYPE_1__* nor; int /*<<< orphan*/  has_second_chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_MCR ; 
 int QUADSPI_MCR_MDIS_MASK ; 
 scalar_t__ QUADSPI_RSER ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct fsl_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qspi_writel (struct fsl_qspi*,int,scalar_t__) ; 

__attribute__((used)) static int fsl_qspi_remove(struct platform_device *pdev)
{
	struct fsl_qspi *q = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < q->nor_num; i++) {
		/* skip the holes */
		if (!q->has_second_chip)
			i *= 2;
		mtd_device_unregister(&q->nor[i].mtd);
	}

	/* disable the hardware */
	qspi_writel(q, QUADSPI_MCR_MDIS_MASK, q->iobase + QUADSPI_MCR);
	qspi_writel(q, 0x0, q->iobase + QUADSPI_RSER);

	mutex_destroy(&q->lock);

	if (q->ahb_addr)
		iounmap(q->ahb_addr);

	return 0;
}