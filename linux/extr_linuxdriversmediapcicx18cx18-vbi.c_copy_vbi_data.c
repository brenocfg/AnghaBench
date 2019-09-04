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
struct v4l2_sliced_vbi_data {scalar_t__ id; int line; int field; int* data; } ;
struct TYPE_2__ {int frame; int** sliced_mpeg_data; int* sliced_mpeg_size; struct v4l2_sliced_vbi_data* sliced_data; } ;
struct cx18 {TYPE_1__ vbi; } ;
typedef  int /*<<< orphan*/  mpeg_hdr_data ;

/* Variables and functions */
 int CX18_VBI_FRAMES ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int cx18_service2vbi (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,...) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

__attribute__((used)) static void copy_vbi_data(struct cx18 *cx, int lines, u32 pts_stamp)
{
	int line = 0;
	int i;
	u32 linemask[2] = { 0, 0 };
	unsigned short size;
	static const u8 mpeg_hdr_data[] = {
		/* MPEG-2 Program Pack */
		0x00, 0x00, 0x01, 0xba,		    /* Prog Pack start code */
		0x44, 0x00, 0x0c, 0x66, 0x24, 0x01, /* SCR, SCR Ext, markers */
		0x01, 0xd1, 0xd3,		    /* Mux Rate, markers */
		0xfa, 0xff, 0xff,		    /* Res, Suff cnt, Stuff */
		/* MPEG-2 Private Stream 1 PES Packet */
		0x00, 0x00, 0x01, 0xbd,		    /* Priv Stream 1 start */
		0x00, 0x1a,			    /* length */
		0x84, 0x80, 0x07,		    /* flags, hdr data len */
		0x21, 0x00, 0x5d, 0x63, 0xa7,	    /* PTS, markers */
		0xff, 0xff			    /* stuffing */
	};
	const int sd = sizeof(mpeg_hdr_data);	/* start of vbi data */
	int idx = cx->vbi.frame % CX18_VBI_FRAMES;
	u8 *dst = &cx->vbi.sliced_mpeg_data[idx][0];

	for (i = 0; i < lines; i++) {
		struct v4l2_sliced_vbi_data *sdata = cx->vbi.sliced_data + i;
		int f, l;

		if (sdata->id == 0)
			continue;

		l = sdata->line - 6;
		f = sdata->field;
		if (f)
			l += 18;
		if (l < 32)
			linemask[0] |= (1 << l);
		else
			linemask[1] |= (1 << (l - 32));
		dst[sd + 12 + line * 43] = cx18_service2vbi(sdata->id);
		memcpy(dst + sd + 12 + line * 43 + 1, sdata->data, 42);
		line++;
	}
	memcpy(dst, mpeg_hdr_data, sizeof(mpeg_hdr_data));
	if (line == 36) {
		/* All lines are used, so there is no space for the linemask
		   (the max size of the VBI data is 36 * 43 + 4 bytes).
		   So in this case we use the magic number 'ITV0'. */
		memcpy(dst + sd, "ITV0", 4);
		memmove(dst + sd + 4, dst + sd + 12, line * 43);
		size = 4 + ((43 * line + 3) & ~3);
	} else {
		memcpy(dst + sd, "itv0", 4);
		cpu_to_le32s(&linemask[0]);
		cpu_to_le32s(&linemask[1]);
		memcpy(dst + sd + 4, &linemask[0], 8);
		size = 12 + ((43 * line + 3) & ~3);
	}
	dst[4+16] = (size + 10) >> 8;
	dst[5+16] = (size + 10) & 0xff;
	dst[9+16] = 0x21 | ((pts_stamp >> 29) & 0x6);
	dst[10+16] = (pts_stamp >> 22) & 0xff;
	dst[11+16] = 1 | ((pts_stamp >> 14) & 0xff);
	dst[12+16] = (pts_stamp >> 7) & 0xff;
	dst[13+16] = 1 | ((pts_stamp & 0x7f) << 1);
	cx->vbi.sliced_mpeg_size[idx] = sd + size;
}