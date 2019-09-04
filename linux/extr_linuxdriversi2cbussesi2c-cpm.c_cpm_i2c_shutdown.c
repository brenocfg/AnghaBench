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
struct cpm_i2c {int version; int /*<<< orphan*/  i2c_addr; TYPE_2__* i2c_ram; TYPE_2__* i2c_reg; int /*<<< orphan*/  dp_addr; int /*<<< orphan*/ * txdma; int /*<<< orphan*/ * txbuf; TYPE_1__* ofdev; int /*<<< orphan*/ * rxdma; int /*<<< orphan*/ * rxbuf; int /*<<< orphan*/  adap; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2cer; int /*<<< orphan*/  i2cmr; int /*<<< orphan*/  i2mod; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CPM_MAXBD ; 
 scalar_t__ CPM_MAX_READ ; 
 int /*<<< orphan*/  I2MOD_EN ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_muram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (TYPE_2__*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cpm_i2c_shutdown(struct cpm_i2c *cpm)
{
	int i;

	/* Shut down I2C. */
	clrbits8(&cpm->i2c_reg->i2mod, I2MOD_EN);

	/* Disable interrupts */
	out_8(&cpm->i2c_reg->i2cmr, 0);
	out_8(&cpm->i2c_reg->i2cer, 0xff);

	free_irq(cpm->irq, &cpm->adap);

	/* Free all memory */
	for (i = 0; i < CPM_MAXBD; i++) {
		dma_free_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
			cpm->rxbuf[i], cpm->rxdma[i]);
		dma_free_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
			cpm->txbuf[i], cpm->txdma[i]);
	}

	cpm_muram_free(cpm->dp_addr);
	iounmap(cpm->i2c_reg);

	if ((cpm->version == 1) && (!cpm->i2c_addr))
		iounmap(cpm->i2c_ram);
	if (cpm->version == 2)
		cpm_muram_free(cpm->i2c_addr);
}