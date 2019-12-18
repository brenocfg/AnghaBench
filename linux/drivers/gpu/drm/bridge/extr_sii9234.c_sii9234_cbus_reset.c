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
struct sii9234 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CBUS_RESET ; 
 int /*<<< orphan*/  MHL_TX_SRST ; 
 int /*<<< orphan*/  T_SRC_CBUS_DEGLITCH ; 
 int /*<<< orphan*/  cbus_writeb (struct sii9234*,int,int) ; 
 int /*<<< orphan*/  mhl_tx_writebm (struct sii9234*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int sii9234_clear_error (struct sii9234*) ; 

__attribute__((used)) static int sii9234_cbus_reset(struct sii9234 *ctx)
{
	int i;

	mhl_tx_writebm(ctx, MHL_TX_SRST, ~0, BIT_CBUS_RESET);
	msleep(T_SRC_CBUS_DEGLITCH);
	mhl_tx_writebm(ctx, MHL_TX_SRST, 0, BIT_CBUS_RESET);

	for (i = 0; i < 4; i++) {
		/*
		 * Enable WRITE_STAT interrupt for writes to all
		 * 4 MSC Status registers.
		 */
		cbus_writeb(ctx, 0xE0 + i, 0xF2);
		/*
		 * Enable SET_INT interrupt for writes to all
		 * 4 MSC Interrupt registers.
		 */
		cbus_writeb(ctx, 0xF0 + i, 0xF2);
	}

	return sii9234_clear_error(ctx);
}