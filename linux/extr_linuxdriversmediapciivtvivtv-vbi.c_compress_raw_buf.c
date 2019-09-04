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
typedef  int u32 ;
struct TYPE_2__ {int raw_decoder_line_size; int count; int raw_decoder_sav_odd_field; int raw_decoder_sav_even_field; } ;
struct ivtv {TYPE_1__ vbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static u32 compress_raw_buf(struct ivtv *itv, u8 *buf, u32 size)
{
	u32 line_size = itv->vbi.raw_decoder_line_size;
	u32 lines = itv->vbi.count;
	u8 sav1 = itv->vbi.raw_decoder_sav_odd_field;
	u8 sav2 = itv->vbi.raw_decoder_sav_even_field;
	u8 *q = buf;
	u8 *p;
	int i;

	for (i = 0; i < lines; i++) {
		p = buf + i * line_size;

		/* Look for SAV code */
		if (p[0] != 0xff || p[1] || p[2] || (p[3] != sav1 && p[3] != sav2)) {
			break;
		}
		memcpy(q, p + 4, line_size - 4);
		q += line_size - 4;
	}
	return lines * (line_size - 4);
}