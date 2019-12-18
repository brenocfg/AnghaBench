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
struct sii8620 {int /*<<< orphan*/  xdevcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_XDC_SIZE ; 
 int /*<<< orphan*/  REG_EDID_FIFO_RD_DATA ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_mr_xdevcap(struct sii8620 *ctx)
{
	sii8620_read_buf(ctx, REG_EDID_FIFO_RD_DATA, ctx->xdevcap,
			 MHL_XDC_SIZE);
}