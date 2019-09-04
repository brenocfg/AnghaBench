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
struct TYPE_2__ {int count; } ;
struct cx18 {TYPE_1__ vbi; } ;

/* Variables and functions */
 int VBI_ACTIVE_SAMPLES ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* raw_vbi_sav_rp ; 

__attribute__((used)) static u32 compress_raw_buf(struct cx18 *cx, u8 *buf, u32 size, u32 hdr_size)
{
	u32 line_size = VBI_ACTIVE_SAMPLES;
	u32 lines = cx->vbi.count * 2;
	u8 *q = buf;
	u8 *p;
	int i;

	/* Skip the header */
	buf += hdr_size;

	for (i = 0; i < lines; i++) {
		p = buf + i * line_size;

		/* Look for SAV code */
		if (p[0] != 0xff || p[1] || p[2] ||
		    (p[3] != raw_vbi_sav_rp[0] &&
		     p[3] != raw_vbi_sav_rp[1]))
			break;
		if (i == lines - 1) {
			/* last line is hdr_size bytes short - extrapolate it */
			memcpy(q, p + 4, line_size - 4 - hdr_size);
			q += line_size - 4 - hdr_size;
			p += line_size - hdr_size - 1;
			memset(q, (int) *p, hdr_size);
		} else {
			memcpy(q, p + 4, line_size - 4);
			q += line_size - 4;
		}
	}
	return lines * (line_size - 4);
}