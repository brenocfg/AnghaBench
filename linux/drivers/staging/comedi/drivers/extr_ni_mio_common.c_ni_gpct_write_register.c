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
struct ni_gpct {TYPE_1__* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_2__ {struct comedi_device* dev; } ;

/* Variables and functions */
 int NISTC_INTA_ENA_G0_GATE ; 
 int NISTC_INTA_ENA_G0_TC ; 
 int NISTC_INTB_ENA_G1_GATE ; 
 int NISTC_INTB_ENA_G1_TC ; 
#define  NITIO_G0_ABZ 141 
#define  NITIO_G0_CNT_MODE 140 
#define  NITIO_G0_DMA_CFG 139 
#define  NITIO_G0_GATE2 138 
#define  NITIO_G0_INT_ENA 137 
#define  NITIO_G0_LOADA 136 
#define  NITIO_G0_LOADB 135 
#define  NITIO_G1_ABZ 134 
#define  NITIO_G1_CNT_MODE 133 
#define  NITIO_G1_DMA_CFG 132 
#define  NITIO_G1_GATE2 131 
#define  NITIO_G1_INT_ENA 130 
#define  NITIO_G1_LOADA 129 
#define  NITIO_G1_LOADB 128 
 unsigned int ni_gpct_to_stc_register (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  ni_stc_writel (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static void ni_gpct_write_register(struct ni_gpct *counter, unsigned int bits,
				   enum ni_gpct_register reg)
{
	struct comedi_device *dev = counter->counter_dev->dev;
	unsigned int stc_register = ni_gpct_to_stc_register(dev, reg);

	if (stc_register == 0)
		return;

	switch (reg) {
		/* m-series only registers */
	case NITIO_G0_CNT_MODE:
	case NITIO_G1_CNT_MODE:
	case NITIO_G0_GATE2:
	case NITIO_G1_GATE2:
	case NITIO_G0_DMA_CFG:
	case NITIO_G1_DMA_CFG:
	case NITIO_G0_ABZ:
	case NITIO_G1_ABZ:
		ni_writew(dev, bits, stc_register);
		break;

		/* 32 bit registers */
	case NITIO_G0_LOADA:
	case NITIO_G1_LOADA:
	case NITIO_G0_LOADB:
	case NITIO_G1_LOADB:
		ni_stc_writel(dev, bits, stc_register);
		break;

		/* 16 bit registers */
	case NITIO_G0_INT_ENA:
		ni_set_bitfield(dev, stc_register,
				NISTC_INTA_ENA_G0_GATE | NISTC_INTA_ENA_G0_TC,
				bits);
		break;
	case NITIO_G1_INT_ENA:
		ni_set_bitfield(dev, stc_register,
				NISTC_INTB_ENA_G1_GATE | NISTC_INTB_ENA_G1_TC,
				bits);
		break;
	default:
		ni_stc_writew(dev, bits, stc_register);
	}
}