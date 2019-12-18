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
struct TYPE_2__ {int tx_count; int* tx_buf; scalar_t__ r_count; scalar_t__ r_size; scalar_t__ rx_ack; } ;
struct sii8620 {TYPE_1__ burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EMSC_XMIT_WRITE_PORT ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  sii8620_write_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sii8620_burst_send(struct sii8620 *ctx)
{
	int tx_left = ctx->burst.tx_count;
	u8 *d = ctx->burst.tx_buf;

	while (tx_left > 0) {
		int len = d[1] + 2;

		if (ctx->burst.r_count + len > ctx->burst.r_size)
			break;
		d[0] = min(ctx->burst.rx_ack, 255);
		ctx->burst.rx_ack -= d[0];
		sii8620_write_buf(ctx, REG_EMSC_XMIT_WRITE_PORT, d, len);
		ctx->burst.r_count += len;
		tx_left -= len;
		d += len;
	}

	ctx->burst.tx_count = tx_left;

	while (ctx->burst.rx_ack > 0) {
		u8 b[2] = { min(ctx->burst.rx_ack, 255), 0 };

		if (ctx->burst.r_count + 2 > ctx->burst.r_size)
			break;
		ctx->burst.rx_ack -= b[0];
		sii8620_write_buf(ctx, REG_EMSC_XMIT_WRITE_PORT, b, 2);
		ctx->burst.r_count += 2;
	}
}