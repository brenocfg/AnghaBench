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
typedef  int u8 ;
typedef  int u16 ;
struct vim2m_q_data {struct vim2m_fmt* fmt; } ;
struct vim2m_fmt {int fourcc; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  V4L2_PIX_FMT_BGR24 136 
#define  V4L2_PIX_FMT_RGB24 135 
#define  V4L2_PIX_FMT_RGB565 134 
#define  V4L2_PIX_FMT_RGB565X 133 
#define  V4L2_PIX_FMT_SBGGR8 132 
#define  V4L2_PIX_FMT_SGBRG8 131 
#define  V4L2_PIX_FMT_SGRBG8 130 
#define  V4L2_PIX_FMT_SRGGB8 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_two_pixels(struct vim2m_q_data *q_data_in,
			    struct vim2m_q_data *q_data_out,
			    u8 *src[2], u8 **dst, int ypos, bool reverse)
{
	struct vim2m_fmt *out = q_data_out->fmt;
	struct vim2m_fmt *in = q_data_in->fmt;
	u8 _r[2], _g[2], _b[2], *r, *g, *b;
	int i;

	/* Step 1: read two consecutive pixels from src pointer */

	r = _r;
	g = _g;
	b = _b;

	switch (in->fourcc) {
	case V4L2_PIX_FMT_RGB565: /* rrrrrggg gggbbbbb */
		for (i = 0; i < 2; i++) {
			u16 pix = le16_to_cpu(*(__le16 *)(src[i]));

			*r++ = (u8)(((pix & 0xf800) >> 11) << 3) | 0x07;
			*g++ = (u8)((((pix & 0x07e0) >> 5)) << 2) | 0x03;
			*b++ = (u8)((pix & 0x1f) << 3) | 0x07;
		}
		break;
	case V4L2_PIX_FMT_RGB565X: /* gggbbbbb rrrrrggg */
		for (i = 0; i < 2; i++) {
			u16 pix = be16_to_cpu(*(__be16 *)(src[i]));

			*r++ = (u8)(((pix & 0xf800) >> 11) << 3) | 0x07;
			*g++ = (u8)((((pix & 0x07e0) >> 5)) << 2) | 0x03;
			*b++ = (u8)((pix & 0x1f) << 3) | 0x07;
		}
		break;
	default:
	case V4L2_PIX_FMT_RGB24:
		for (i = 0; i < 2; i++) {
			*r++ = src[i][0];
			*g++ = src[i][1];
			*b++ = src[i][2];
		}
		break;
	case V4L2_PIX_FMT_BGR24:
		for (i = 0; i < 2; i++) {
			*b++ = src[i][0];
			*g++ = src[i][1];
			*r++ = src[i][2];
		}
		break;
	}

	/* Step 2: store two consecutive points, reversing them if needed */

	r = _r;
	g = _g;
	b = _b;

	switch (out->fourcc) {
	case V4L2_PIX_FMT_RGB565: /* rrrrrggg gggbbbbb */
		for (i = 0; i < 2; i++) {
			u16 pix;
			__le16 *dst_pix = (__le16 *)*dst;

			pix = ((*r << 8) & 0xf800) | ((*g << 3) & 0x07e0) |
			      (*b >> 3);

			*dst_pix = cpu_to_le16(pix);

			*dst += 2;
		}
		return;
	case V4L2_PIX_FMT_RGB565X: /* gggbbbbb rrrrrggg */
		for (i = 0; i < 2; i++) {
			u16 pix;
			__be16 *dst_pix = (__be16 *)*dst;

			pix = ((*r << 8) & 0xf800) | ((*g << 3) & 0x07e0) |
			      (*b >> 3);

			*dst_pix = cpu_to_be16(pix);

			*dst += 2;
		}
		return;
	case V4L2_PIX_FMT_RGB24:
		for (i = 0; i < 2; i++) {
			*(*dst)++ = *r++;
			*(*dst)++ = *g++;
			*(*dst)++ = *b++;
		}
		return;
	case V4L2_PIX_FMT_BGR24:
		for (i = 0; i < 2; i++) {
			*(*dst)++ = *b++;
			*(*dst)++ = *g++;
			*(*dst)++ = *r++;
		}
		return;
	case V4L2_PIX_FMT_YUYV:
	default:
	{
		u8 y, y1, u, v;

		y = ((8453  * (*r) + 16594 * (*g) +  3223 * (*b)
		     + 524288) >> 15);
		u = ((-4878 * (*r) - 9578  * (*g) + 14456 * (*b)
		     + 4210688) >> 15);
		v = ((14456 * (*r++) - 12105 * (*g++) - 2351 * (*b++)
		     + 4210688) >> 15);
		y1 = ((8453 * (*r) + 16594 * (*g) +  3223 * (*b)
		     + 524288) >> 15);

		*(*dst)++ = y;
		*(*dst)++ = u;

		*(*dst)++ = y1;
		*(*dst)++ = v;
		return;
	}
	case V4L2_PIX_FMT_SBGGR8:
		if (!(ypos & 1)) {
			*(*dst)++ = *b;
			*(*dst)++ = *++g;
		} else {
			*(*dst)++ = *g;
			*(*dst)++ = *++r;
		}
		return;
	case V4L2_PIX_FMT_SGBRG8:
		if (!(ypos & 1)) {
			*(*dst)++ = *g;
			*(*dst)++ = *++b;
		} else {
			*(*dst)++ = *r;
			*(*dst)++ = *++g;
		}
		return;
	case V4L2_PIX_FMT_SGRBG8:
		if (!(ypos & 1)) {
			*(*dst)++ = *g;
			*(*dst)++ = *++r;
		} else {
			*(*dst)++ = *b;
			*(*dst)++ = *++g;
		}
		return;
	case V4L2_PIX_FMT_SRGGB8:
		if (!(ypos & 1)) {
			*(*dst)++ = *r;
			*(*dst)++ = *++g;
		} else {
			*(*dst)++ = *g;
			*(*dst)++ = *++b;
		}
		return;
	}
}