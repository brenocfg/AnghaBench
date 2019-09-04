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
struct sii8620 {int gen2_write_burst; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN ; 
 int /*<<< orphan*/  BIT_MDT_RCV_CTRL_MDT_RCV_EN ; 
 scalar_t__ CM_MHL1 ; 
 int /*<<< orphan*/  REG_MDT_RCV_CTRL ; 
 int /*<<< orphan*/  REG_MDT_RCV_TIMEOUT ; 
 int /*<<< orphan*/  sii8620_write_seq (struct sii8620*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_enable_gen2_write_burst(struct sii8620 *ctx)
{
	u8 ctrl = BIT_MDT_RCV_CTRL_MDT_RCV_EN;

	if (ctx->gen2_write_burst)
		return;

	if (ctx->mode >= CM_MHL1)
		ctrl |= BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN;

	sii8620_write_seq(ctx,
		REG_MDT_RCV_TIMEOUT, 100,
		REG_MDT_RCV_CTRL, ctrl
	);
	ctx->gen2_write_burst = 1;
}