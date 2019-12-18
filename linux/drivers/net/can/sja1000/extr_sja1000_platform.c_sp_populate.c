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
struct TYPE_3__ {int freq; } ;
struct TYPE_4__ {TYPE_1__ clock; } ;
struct sja1000_priv {int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  cdr; int /*<<< orphan*/  ocr; TYPE_2__ can; } ;
struct sja1000_platform_data {int osc_freq; int /*<<< orphan*/  cdr; int /*<<< orphan*/  ocr; } ;

/* Variables and functions */
#define  IORESOURCE_MEM_16BIT 130 
#define  IORESOURCE_MEM_32BIT 129 
#define  IORESOURCE_MEM_8BIT 128 
 unsigned long IORESOURCE_MEM_TYPE_MASK ; 
 int /*<<< orphan*/  sp_read_reg16 ; 
 int /*<<< orphan*/  sp_read_reg32 ; 
 int /*<<< orphan*/  sp_read_reg8 ; 
 int /*<<< orphan*/  sp_write_reg16 ; 
 int /*<<< orphan*/  sp_write_reg32 ; 
 int /*<<< orphan*/  sp_write_reg8 ; 

__attribute__((used)) static void sp_populate(struct sja1000_priv *priv,
			struct sja1000_platform_data *pdata,
			unsigned long resource_mem_flags)
{
	/* The CAN clock frequency is half the oscillator clock frequency */
	priv->can.clock.freq = pdata->osc_freq / 2;
	priv->ocr = pdata->ocr;
	priv->cdr = pdata->cdr;

	switch (resource_mem_flags & IORESOURCE_MEM_TYPE_MASK) {
	case IORESOURCE_MEM_32BIT:
		priv->read_reg = sp_read_reg32;
		priv->write_reg = sp_write_reg32;
		break;
	case IORESOURCE_MEM_16BIT:
		priv->read_reg = sp_read_reg16;
		priv->write_reg = sp_write_reg16;
		break;
	case IORESOURCE_MEM_8BIT:
	default:
		priv->read_reg = sp_read_reg8;
		priv->write_reg = sp_write_reg8;
		break;
	}
}