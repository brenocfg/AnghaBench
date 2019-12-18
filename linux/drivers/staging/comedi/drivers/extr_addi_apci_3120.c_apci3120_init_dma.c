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
struct comedi_device {struct apci3120_private* private; } ;
struct apci3120_private {scalar_t__ addon; scalar_t__ amcc; } ;
struct apci3120_dmabuf {int hw; int use_size; } ;

/* Variables and functions */
 int AGCSTS_RESET_A2P_FIFO ; 
 int AGCSTS_TC_ENABLE ; 
 int AINT_WRITE_COMPL ; 
 scalar_t__ AMCC_OP_REG_AGCSTS ; 
 scalar_t__ AMCC_OP_REG_AMWAR ; 
 scalar_t__ AMCC_OP_REG_AMWTC ; 
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 scalar_t__ AMCC_OP_REG_MCSR ; 
 int APCI3120_ADDON_CTRL_A2P_FIFO_ENA ; 
 int APCI3120_ADDON_CTRL_AMWEN_ENA ; 
 scalar_t__ APCI3120_ADDON_CTRL_REG ; 
 int APCI3120_FIFO_ADVANCE_ON_BYTE_2 ; 
 int EN_A2P_TRANSFERS ; 
 int RESET_A2P_FLAGS ; 
 int /*<<< orphan*/  apci3120_addon_write (struct comedi_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void apci3120_init_dma(struct comedi_device *dev,
			      struct apci3120_dmabuf *dmabuf)
{
	struct apci3120_private *devpriv = dev->private;

	/* AMCC - enable transfer count and reset A2P FIFO */
	outl(AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO,
	     devpriv->amcc + AMCC_OP_REG_AGCSTS);

	/* Add-On - enable transfer count and reset A2P FIFO */
	apci3120_addon_write(dev, AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO,
			     AMCC_OP_REG_AGCSTS);

	/* AMCC - enable transfers and reset A2P flags */
	outl(RESET_A2P_FLAGS | EN_A2P_TRANSFERS,
	     devpriv->amcc + AMCC_OP_REG_MCSR);

	/* Add-On - DMA start address */
	apci3120_addon_write(dev, dmabuf->hw, AMCC_OP_REG_AMWAR);

	/* Add-On - Number of acquisitions */
	apci3120_addon_write(dev, dmabuf->use_size, AMCC_OP_REG_AMWTC);

	/* AMCC - enable write complete (DMA) and set FIFO advance */
	outl(APCI3120_FIFO_ADVANCE_ON_BYTE_2 | AINT_WRITE_COMPL,
	     devpriv->amcc + AMCC_OP_REG_INTCSR);

	/* Add-On - enable DMA */
	outw(APCI3120_ADDON_CTRL_AMWEN_ENA | APCI3120_ADDON_CTRL_A2P_FIFO_ENA,
	     devpriv->addon + APCI3120_ADDON_CTRL_REG);
}