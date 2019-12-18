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
typedef  int /*<<< orphan*/  u8 ;
struct vivid_dev {int sdr_adc_freq; int sdr_fixp_src_phase; int sdr_fm_deviation; int sdr_fixp_mod_phase; int sdr_pixelformat; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct vivid_buffer {TYPE_1__ vb; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int BEEP_FREQ ; 
 void* DIV_ROUND_CLOSEST (int,int) ; 
 int FIXP_2PI ; 
 int FIXP_FRAC ; 
 int FIXP_N ; 
 int /*<<< orphan*/  M_100000PI ; 
#define  V4L2_SDR_FMT_CS8 129 
#define  V4L2_SDR_FMT_CU8 128 
 scalar_t__ div_s64 (int,int /*<<< orphan*/ ) ; 
 int fixp_cos32_rad (int,int) ; 
 int fixp_sin32_rad (int,int) ; 
 unsigned long vb2_plane_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vivid_sdr_cap_process(struct vivid_dev *dev, struct vivid_buffer *buf)
{
	u8 *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	unsigned long i;
	unsigned long plane_size = vb2_plane_size(&buf->vb.vb2_buf, 0);
	s64 s64tmp;
	s32 src_phase_step;
	s32 mod_phase_step;
	s32 fixp_i;
	s32 fixp_q;

	/* calculate phase step */
	#define BEEP_FREQ 1000 /* 1kHz beep */
	src_phase_step = DIV_ROUND_CLOSEST(FIXP_2PI * BEEP_FREQ,
					   dev->sdr_adc_freq);

	for (i = 0; i < plane_size; i += 2) {
		mod_phase_step = fixp_cos32_rad(dev->sdr_fixp_src_phase,
						FIXP_2PI) >> (31 - FIXP_N);

		dev->sdr_fixp_src_phase += src_phase_step;
		s64tmp = (s64) mod_phase_step * dev->sdr_fm_deviation;
		dev->sdr_fixp_mod_phase += div_s64(s64tmp, M_100000PI);

		/*
		 * Transfer phase angle to [0, 2xPI] in order to avoid variable
		 * overflow and make it suitable for cosine implementation
		 * used, which does not support negative angles.
		 */
		dev->sdr_fixp_src_phase %= FIXP_2PI;
		dev->sdr_fixp_mod_phase %= FIXP_2PI;

		if (dev->sdr_fixp_mod_phase < 0)
			dev->sdr_fixp_mod_phase += FIXP_2PI;

		fixp_i = fixp_cos32_rad(dev->sdr_fixp_mod_phase, FIXP_2PI);
		fixp_q = fixp_sin32_rad(dev->sdr_fixp_mod_phase, FIXP_2PI);

		/* Normalize fraction values represented with 32 bit precision
		 * to fixed point representation with FIXP_N bits */
		fixp_i >>= (31 - FIXP_N);
		fixp_q >>= (31 - FIXP_N);

		switch (dev->sdr_pixelformat) {
		case V4L2_SDR_FMT_CU8:
			/* convert 'fixp float' to u8 [0, +255] */
			/* u8 = X * 127.5 + 127.5; X is float [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 + FIXP_FRAC * 1275;
			fixp_q = fixp_q * 1275 + FIXP_FRAC * 1275;
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_i, FIXP_FRAC * 10);
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_q, FIXP_FRAC * 10);
			break;
		case V4L2_SDR_FMT_CS8:
			/* convert 'fixp float' to s8 [-128, +127] */
			/* s8 = X * 127.5 - 0.5; X is float [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 - FIXP_FRAC * 5;
			fixp_q = fixp_q * 1275 - FIXP_FRAC * 5;
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_i, FIXP_FRAC * 10);
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_q, FIXP_FRAC * 10);
			break;
		default:
			break;
		}
	}
}