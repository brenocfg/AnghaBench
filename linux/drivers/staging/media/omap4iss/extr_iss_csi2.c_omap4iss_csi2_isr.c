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
typedef  int u32 ;
struct iss_pipeline {int error; } ;
struct iss_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct iss_csi2_device {int /*<<< orphan*/ * contexts; int /*<<< orphan*/  regs1; struct iss_device* iss; int /*<<< orphan*/  available; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_COMPLEXIO_IRQSTATUS ; 
 int /*<<< orphan*/  CSI2_IRQSTATUS ; 
 int CSI2_IRQ_COMPLEXIO_ERR ; 
 int CSI2_IRQ_CONTEXT0 ; 
 int CSI2_IRQ_ECC_CORRECTION ; 
 int CSI2_IRQ_ECC_NO_CORRECTION ; 
 int CSI2_IRQ_FIFO_OVF ; 
 int CSI2_IRQ_OCP_ERR ; 
 int CSI2_IRQ_SHORT_PACKET ; 
 int /*<<< orphan*/  csi2_isr_ctx (struct iss_csi2_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int iss_reg_read (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iss_pipeline* to_iss_pipeline (int /*<<< orphan*/ *) ; 

void omap4iss_csi2_isr(struct iss_csi2_device *csi2)
{
	struct iss_pipeline *pipe = to_iss_pipeline(&csi2->subdev.entity);
	u32 csi2_irqstatus, cpxio1_irqstatus;
	struct iss_device *iss = csi2->iss;

	if (!csi2->available)
		return;

	csi2_irqstatus = iss_reg_read(csi2->iss, csi2->regs1, CSI2_IRQSTATUS);
	iss_reg_write(csi2->iss, csi2->regs1, CSI2_IRQSTATUS, csi2_irqstatus);

	/* Failure Cases */
	if (csi2_irqstatus & CSI2_IRQ_COMPLEXIO_ERR) {
		cpxio1_irqstatus = iss_reg_read(csi2->iss, csi2->regs1,
						CSI2_COMPLEXIO_IRQSTATUS);
		iss_reg_write(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_IRQSTATUS,
			      cpxio1_irqstatus);
		dev_dbg(iss->dev, "CSI2: ComplexIO Error IRQ %x\n",
			cpxio1_irqstatus);
		pipe->error = true;
	}

	if (csi2_irqstatus & (CSI2_IRQ_OCP_ERR |
			      CSI2_IRQ_SHORT_PACKET |
			      CSI2_IRQ_ECC_NO_CORRECTION |
			      CSI2_IRQ_COMPLEXIO_ERR |
			      CSI2_IRQ_FIFO_OVF)) {
		dev_dbg(iss->dev,
			"CSI2 Err: OCP:%d SHORT:%d ECC:%d CPXIO:%d OVF:%d\n",
			csi2_irqstatus & CSI2_IRQ_OCP_ERR ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_SHORT_PACKET ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_ECC_NO_CORRECTION ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_COMPLEXIO_ERR ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_FIFO_OVF ? 1 : 0);
		pipe->error = true;
	}

	/* Successful cases */
	if (csi2_irqstatus & CSI2_IRQ_CONTEXT0)
		csi2_isr_ctx(csi2, &csi2->contexts[0]);

	if (csi2_irqstatus & CSI2_IRQ_ECC_CORRECTION)
		dev_dbg(iss->dev, "CSI2: ECC correction done\n");
}