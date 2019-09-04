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
typedef  int u32 ;
struct snd_dw_hdmi {int* buf_src; int* buf_dst; int iec_offset; unsigned int channels; int /*<<< orphan*/ ** cs; } ;

/* Variables and functions */
 int parity (int) ; 

__attribute__((used)) static void dw_hdmi_reformat_s24(struct snd_dw_hdmi *dw,
	size_t offset, size_t bytes)
{
	u32 *src = dw->buf_src + offset;
	u32 *dst = dw->buf_dst + offset;
	u32 *end = dw->buf_src + offset + bytes;

	do {
		unsigned i;
		u8 *cs;

		cs = dw->cs[dw->iec_offset++];
		if (dw->iec_offset >= 192)
			dw->iec_offset = 0;

		i = dw->channels;
		do {
			u32 sample = *src++;

			sample &= ~0xff000000;
			sample |= *cs++ << 24;
			sample |= parity(sample & ~0xf8000000);

			*dst++ = sample;
		} while (--i);
	} while (src < end);
}