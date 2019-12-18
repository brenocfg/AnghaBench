#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sii8620 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  checksum; } ;
struct mhl_burst_bits_per_pixel_fmt {int num_entries; TYPE_2__ hdr; TYPE_1__* desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixel_format; scalar_t__ stream_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_BURST_ID_BITS_PER_PIXEL_FMT ; 
 struct mhl_burst_bits_per_pixel_fmt* sii8620_burst_get_tx_buf (struct sii8620*,int const) ; 
 scalar_t__ sii8620_checksum (struct mhl_burst_bits_per_pixel_fmt*,int const) ; 
 int /*<<< orphan*/  sii8620_mhl_burst_hdr_set (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_burst_tx_bits_per_pixel_fmt(struct sii8620 *ctx, u8 fmt)
{
	struct mhl_burst_bits_per_pixel_fmt *d;
	const int size = sizeof(*d) + sizeof(d->desc[0]);

	d = sii8620_burst_get_tx_buf(ctx, size);
	if (!d)
		return;

	sii8620_mhl_burst_hdr_set(&d->hdr, MHL_BURST_ID_BITS_PER_PIXEL_FMT);
	d->num_entries = 1;
	d->desc[0].stream_id = 0;
	d->desc[0].pixel_format = fmt;
	d->hdr.checksum -= sii8620_checksum(d, size);
}