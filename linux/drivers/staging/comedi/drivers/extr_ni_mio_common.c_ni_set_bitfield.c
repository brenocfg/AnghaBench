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
struct ni_private {unsigned int int_a_enable_reg; unsigned int int_b_enable_reg; unsigned int io_bidirection_pin_reg; unsigned int ai_ao_select_reg; unsigned int g0_g1_select_reg; unsigned int cdio_dma_select_reg; int /*<<< orphan*/  soft_reg_copy_lock; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
#define  NISTC_INTA_ENA_REG 133 
#define  NISTC_INTB_ENA_REG 132 
#define  NISTC_IO_BIDIR_PIN_REG 131 
#define  NI_E_DMA_AI_AO_SEL_REG 130 
#define  NI_E_DMA_G0_G1_SEL_REG 129 
#define  NI_M_CDIO_DMA_SEL_REG 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ni_set_bitfield(struct comedi_device *dev, int reg,
				   unsigned int bit_mask,
				   unsigned int bit_values)
{
	struct ni_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->soft_reg_copy_lock, flags);
	switch (reg) {
	case NISTC_INTA_ENA_REG:
		devpriv->int_a_enable_reg &= ~bit_mask;
		devpriv->int_a_enable_reg |= bit_values & bit_mask;
		ni_stc_writew(dev, devpriv->int_a_enable_reg, reg);
		break;
	case NISTC_INTB_ENA_REG:
		devpriv->int_b_enable_reg &= ~bit_mask;
		devpriv->int_b_enable_reg |= bit_values & bit_mask;
		ni_stc_writew(dev, devpriv->int_b_enable_reg, reg);
		break;
	case NISTC_IO_BIDIR_PIN_REG:
		devpriv->io_bidirection_pin_reg &= ~bit_mask;
		devpriv->io_bidirection_pin_reg |= bit_values & bit_mask;
		ni_stc_writew(dev, devpriv->io_bidirection_pin_reg, reg);
		break;
	case NI_E_DMA_AI_AO_SEL_REG:
		devpriv->ai_ao_select_reg &= ~bit_mask;
		devpriv->ai_ao_select_reg |= bit_values & bit_mask;
		ni_writeb(dev, devpriv->ai_ao_select_reg, reg);
		break;
	case NI_E_DMA_G0_G1_SEL_REG:
		devpriv->g0_g1_select_reg &= ~bit_mask;
		devpriv->g0_g1_select_reg |= bit_values & bit_mask;
		ni_writeb(dev, devpriv->g0_g1_select_reg, reg);
		break;
	case NI_M_CDIO_DMA_SEL_REG:
		devpriv->cdio_dma_select_reg &= ~bit_mask;
		devpriv->cdio_dma_select_reg |= bit_values & bit_mask;
		ni_writeb(dev, devpriv->cdio_dma_select_reg, reg);
		break;
	default:
		dev_err(dev->class_dev, "called with invalid register %d\n",
			reg);
		break;
	}
	spin_unlock_irqrestore(&devpriv->soft_reg_copy_lock, flags);
}