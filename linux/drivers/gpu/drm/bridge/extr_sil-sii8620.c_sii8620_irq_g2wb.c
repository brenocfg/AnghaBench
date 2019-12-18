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
typedef  int u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_MDT_IDLE_AFTER_HAWB_DISABLE ; 
 int BIT_MDT_RFIFO_DATA_RDY ; 
 int BIT_MDT_XFIFO_EMPTY ; 
 int /*<<< orphan*/  MHL_INT_RC_FEAT_COMPLETE ; 
 int /*<<< orphan*/  MHL_INT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCHANGE ; 
 int /*<<< orphan*/  REG_MDT_INT_0 ; 
 int /*<<< orphan*/  REG_MDT_XMIT_CTRL ; 
 scalar_t__ sii8620_is_mhl3 (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mt_set_int (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_read_burst (struct sii8620*) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_g2wb(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_MDT_INT_0);

	if (stat & BIT_MDT_IDLE_AFTER_HAWB_DISABLE)
		if (sii8620_is_mhl3(ctx))
			sii8620_mt_set_int(ctx, MHL_INT_REG(RCHANGE),
				MHL_INT_RC_FEAT_COMPLETE);

	if (stat & BIT_MDT_RFIFO_DATA_RDY)
		sii8620_read_burst(ctx);

	if (stat & BIT_MDT_XFIFO_EMPTY)
		sii8620_write(ctx, REG_MDT_XMIT_CTRL, 0);

	sii8620_write(ctx, REG_MDT_INT_0, stat);
}