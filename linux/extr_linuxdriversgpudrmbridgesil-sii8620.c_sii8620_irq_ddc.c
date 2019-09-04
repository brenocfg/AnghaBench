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
struct sii8620 {int /*<<< orphan*/  feature_complete; } ;

/* Variables and functions */
 int BIT_DDC_CMD_DONE ; 
 int /*<<< orphan*/  MHL_INT_RC_FEAT_REQ ; 
 int /*<<< orphan*/  MHL_INT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCHANGE ; 
 int /*<<< orphan*/  REG_INTR3 ; 
 int /*<<< orphan*/  REG_INTR3_MASK ; 
 int /*<<< orphan*/  sii8620_enable_hpd (struct sii8620*) ; 
 scalar_t__ sii8620_is_mhl3 (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mt_set_int (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_ddc(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_INTR3);

	if (stat & BIT_DDC_CMD_DONE) {
		sii8620_write(ctx, REG_INTR3_MASK, 0);
		if (sii8620_is_mhl3(ctx) && !ctx->feature_complete)
			sii8620_mt_set_int(ctx, MHL_INT_REG(RCHANGE),
					   MHL_INT_RC_FEAT_REQ);
		else
			sii8620_enable_hpd(ctx);
	}
	sii8620_write(ctx, REG_INTR3, stat);
}