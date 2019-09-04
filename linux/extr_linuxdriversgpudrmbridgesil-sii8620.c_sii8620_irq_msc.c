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
struct sii8620 {int cbus_status; int sink_detected; } ;

/* Variables and functions */
 int BIT_CBUS_HPD_CHG ; 
 int BIT_CBUS_MSC_MR_MSC_MSG ; 
 int BIT_CBUS_MSC_MR_SET_INT ; 
 int BIT_CBUS_MSC_MR_WRITE_STAT ; 
 int BIT_CBUS_MSC_MT_DONE ; 
 int BIT_CBUS_STATUS_CBUS_HPD ; 
 int /*<<< orphan*/  REG_CBUS_INT_0 ; 
 int /*<<< orphan*/  REG_CBUS_STATUS ; 
 int /*<<< orphan*/  sii8620_hpd_unplugged (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_identify_sink (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_msc_mr_msc_msg (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_msc_mr_set_int (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_msc_mr_write_stat (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_msc_mt_done (struct sii8620*) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_msc(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_CBUS_INT_0);

	if (stat & ~BIT_CBUS_HPD_CHG)
		sii8620_write(ctx, REG_CBUS_INT_0, stat & ~BIT_CBUS_HPD_CHG);

	if (stat & BIT_CBUS_HPD_CHG) {
		u8 cbus_stat = sii8620_readb(ctx, REG_CBUS_STATUS);

		if ((cbus_stat ^ ctx->cbus_status) & BIT_CBUS_STATUS_CBUS_HPD) {
			sii8620_write(ctx, REG_CBUS_INT_0, BIT_CBUS_HPD_CHG);
		} else {
			stat ^= BIT_CBUS_STATUS_CBUS_HPD;
			cbus_stat ^= BIT_CBUS_STATUS_CBUS_HPD;
		}
		ctx->cbus_status = cbus_stat;
	}

	if (stat & BIT_CBUS_MSC_MR_WRITE_STAT)
		sii8620_msc_mr_write_stat(ctx);

	if (stat & BIT_CBUS_HPD_CHG) {
		if (ctx->cbus_status & BIT_CBUS_STATUS_CBUS_HPD) {
			ctx->sink_detected = true;
			sii8620_identify_sink(ctx);
		} else {
			sii8620_hpd_unplugged(ctx);
		}
	}

	if (stat & BIT_CBUS_MSC_MR_SET_INT)
		sii8620_msc_mr_set_int(ctx);

	if (stat & BIT_CBUS_MSC_MT_DONE)
		sii8620_msc_mt_done(ctx);

	if (stat & BIT_CBUS_MSC_MR_MSC_MSG)
		sii8620_msc_mr_msc_msg(ctx);
}