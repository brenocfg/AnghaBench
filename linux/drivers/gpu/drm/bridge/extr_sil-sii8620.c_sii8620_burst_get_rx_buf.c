#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int* rx_buf; size_t rx_count; scalar_t__ tx_count; int /*<<< orphan*/  tx_buf; } ;
struct sii8620 {TYPE_1__ burst; int /*<<< orphan*/  error; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u8 *sii8620_burst_get_rx_buf(struct sii8620 *ctx, int len)
{
	u8 *buf = &ctx->burst.rx_buf[ctx->burst.rx_count];
	int size = len + 1;

	if (ctx->burst.tx_count + size > ARRAY_SIZE(ctx->burst.tx_buf)) {
		dev_err(ctx->dev, "RX-BLK buffer exhausted\n");
		ctx->error = -EINVAL;
		return NULL;
	}

	ctx->burst.rx_count += size;
	buf[0] = len;

	return buf + 1;
}