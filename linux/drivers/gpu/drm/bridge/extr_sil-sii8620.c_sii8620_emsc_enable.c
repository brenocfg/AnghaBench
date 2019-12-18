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
typedef  int /*<<< orphan*/  u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_COMMECNT_I2C_TO_EMSC_EN ; 
 int /*<<< orphan*/  BIT_EMSCINTR_SPI_DVLD ; 
 int BIT_GENCTL_CLR_EMSC_RFIFO ; 
 int BIT_GENCTL_CLR_EMSC_XFIFO ; 
 int BIT_GENCTL_EMSC_EN ; 
 int /*<<< orphan*/  REG_COMMECNT ; 
 int /*<<< orphan*/  REG_EMSCINTR ; 
 int /*<<< orphan*/  REG_EMSCINTRMASK ; 
 int /*<<< orphan*/  REG_GENCTL ; 
 int /*<<< orphan*/  sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_setbits (struct sii8620*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_emsc_enable(struct sii8620 *ctx)
{
	u8 reg;

	sii8620_setbits(ctx, REG_GENCTL, BIT_GENCTL_EMSC_EN
					 | BIT_GENCTL_CLR_EMSC_RFIFO
					 | BIT_GENCTL_CLR_EMSC_XFIFO, ~0);
	sii8620_setbits(ctx, REG_GENCTL, BIT_GENCTL_CLR_EMSC_RFIFO
					 | BIT_GENCTL_CLR_EMSC_XFIFO, 0);
	sii8620_setbits(ctx, REG_COMMECNT, BIT_COMMECNT_I2C_TO_EMSC_EN, ~0);
	reg = sii8620_readb(ctx, REG_EMSCINTR);
	sii8620_write(ctx, REG_EMSCINTR, reg);
	sii8620_write(ctx, REG_EMSCINTRMASK, BIT_EMSCINTR_SPI_DVLD);
}