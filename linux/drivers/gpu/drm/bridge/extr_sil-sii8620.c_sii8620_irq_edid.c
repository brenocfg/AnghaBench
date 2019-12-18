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
struct sii8620 {int /*<<< orphan*/  mt_state; } ;

/* Variables and functions */
 int BIT_INTR9_DEVCAP_DONE ; 
 int /*<<< orphan*/  MT_STATE_DONE ; 
 int /*<<< orphan*/  REG_INTR9 ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_irq_edid(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_INTR9);

	sii8620_write(ctx, REG_INTR9, stat);

	if (stat & BIT_INTR9_DEVCAP_DONE)
		ctx->mt_state = MT_STATE_DONE;
}