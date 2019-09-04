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
struct sii8620 {scalar_t__ gen2_write_burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDT_RCV_CTRL ; 
 int /*<<< orphan*/  REG_MDT_XMIT_CTRL ; 
 int /*<<< orphan*/  sii8620_write_seq_static (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_disable_gen2_write_burst(struct sii8620 *ctx)
{
	if (!ctx->gen2_write_burst)
		return;

	sii8620_write_seq_static(ctx,
		REG_MDT_XMIT_CTRL, 0,
		REG_MDT_RCV_CTRL, 0
	);
	ctx->gen2_write_burst = 0;
}