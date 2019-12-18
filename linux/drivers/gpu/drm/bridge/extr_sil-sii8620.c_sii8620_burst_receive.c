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
struct TYPE_2__ {int rx_ack; scalar_t__ r_count; } ;
struct sii8620 {TYPE_1__ burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EMSCRFIFOBCNTL ; 
 int /*<<< orphan*/  REG_EMSC_RCV_READ_PORT ; 
 int get_unaligned_le16 (int*) ; 
 int min (int,int) ; 
 int* sii8620_burst_get_rx_buf (struct sii8620*,int) ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sii8620_burst_receive(struct sii8620 *ctx)
{
	u8 buf[3], *d;
	int count;

	sii8620_read_buf(ctx, REG_EMSCRFIFOBCNTL, buf, 2);
	count = get_unaligned_le16(buf);
	while (count > 0) {
		int len = min(count, 3);

		sii8620_read_buf(ctx, REG_EMSC_RCV_READ_PORT, buf, len);
		count -= len;
		ctx->burst.rx_ack += len - 1;
		ctx->burst.r_count -= buf[1];
		if (ctx->burst.r_count < 0)
			ctx->burst.r_count = 0;

		if (len < 3 || !buf[2])
			continue;

		len = buf[2];
		d = sii8620_burst_get_rx_buf(ctx, len);
		if (!d)
			continue;
		sii8620_read_buf(ctx, REG_EMSC_RCV_READ_PORT, d, len);
		count -= len;
		ctx->burst.rx_ack += len;
	}
}