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
 int BIT_CBUS_MHL12_DISCON_INT ; 
 int BIT_CBUS_MHL3_DISCON_INT ; 
 int BIT_DISC_CTRL9_NOMHL_EST ; 
 int BIT_DISC_CTRL9_WAKE_DRVFLT ; 
 int BIT_DISC_CTRL9_WAKE_PULSE_BYPASS ; 
 int BIT_MHL_EST_INT ; 
 int BIT_NOT_MHL_EST_INT ; 
 int BIT_RGND_READY_INT ; 
 int MSK_DISC_STAT2_RGND ; 
 int /*<<< orphan*/  REG_CBUS_DISC_INTR0 ; 
 int /*<<< orphan*/  REG_CBUS_DISC_INTR0_MASK ; 
 int /*<<< orphan*/  REG_DISC_CTRL9 ; 
 int /*<<< orphan*/  REG_DISC_STAT2 ; 
 int VAL_CBUS_MHL_DISCON ; 
 int VAL_RGND_1K ; 
 int /*<<< orphan*/  sii8620_mhl_disconnected (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mhl_discover (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mhl_init (struct sii8620*) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sii8620_write_seq_static (struct sii8620*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_disc(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_CBUS_DISC_INTR0);

	if (stat & VAL_CBUS_MHL_DISCON)
		sii8620_mhl_disconnected(ctx);

	if (stat & BIT_RGND_READY_INT) {
		u8 stat2 = sii8620_readb(ctx, REG_DISC_STAT2);

		if ((stat2 & MSK_DISC_STAT2_RGND) == VAL_RGND_1K) {
			sii8620_mhl_discover(ctx);
		} else {
			sii8620_write_seq_static(ctx,
				REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
					| BIT_DISC_CTRL9_NOMHL_EST
					| BIT_DISC_CTRL9_WAKE_PULSE_BYPASS,
				REG_CBUS_DISC_INTR0_MASK, BIT_RGND_READY_INT
					| BIT_CBUS_MHL3_DISCON_INT
					| BIT_CBUS_MHL12_DISCON_INT
					| BIT_NOT_MHL_EST_INT
			);
		}
	}
	if (stat & BIT_MHL_EST_INT)
		sii8620_mhl_init(ctx);

	sii8620_write(ctx, REG_CBUS_DISC_INTR0, stat);
}