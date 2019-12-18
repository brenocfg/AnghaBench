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
typedef  int u64 ;
typedef  int u32 ;
struct my_timming {unsigned int HTotal; unsigned int VTotal; unsigned int HSyncEnd; unsigned int HSyncStart; unsigned int delay; unsigned int VSyncEnd; unsigned int VSyncStart; int HDisplay; unsigned int VDisplay; int /*<<< orphan*/  pixclock; } ;
struct mavenregs {unsigned int hcorr; unsigned int* regs; int htotal; int vlines; int /*<<< orphan*/  mode; } ;
struct maven_data {scalar_t__ version; struct matrox_fb_info* primary_head; } ;
struct matrox_fb_info {TYPE_1__* outputs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC1064_calcclock (int /*<<< orphan*/ ,int,unsigned int*,unsigned int*,unsigned int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MATROXFB_OUTPUT_MODE_MONITOR ; 
 scalar_t__ MGATVO_B ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 scalar_t__ maven_find_exact_clocks (unsigned int,unsigned int,struct mavenregs*) ; 
 int /*<<< orphan*/  maven_init_TVdata (struct maven_data*,struct mavenregs*) ; 

__attribute__((used)) static inline int maven_compute_timming(struct maven_data* md,
		struct my_timming* mt,
		struct mavenregs* m) {
	unsigned int tmpi;
	unsigned int a, bv, c;
	struct matrox_fb_info *minfo = md->primary_head;

	m->mode = minfo->outputs[1].mode;
	if (m->mode != MATROXFB_OUTPUT_MODE_MONITOR) {
		unsigned int lmargin;
		unsigned int umargin;
		unsigned int vslen;
		unsigned int hcrt;
		unsigned int slen;

		maven_init_TVdata(md, m);

		if (maven_find_exact_clocks(mt->HTotal, mt->VTotal, m) == 0)
			return -EINVAL;

		lmargin = mt->HTotal - mt->HSyncEnd;
		slen = mt->HSyncEnd - mt->HSyncStart;
		hcrt = mt->HTotal - slen - mt->delay;
		umargin = mt->VTotal - mt->VSyncEnd;
		vslen = mt->VSyncEnd - mt->VSyncStart;

		if (m->hcorr < mt->HTotal)
			hcrt += m->hcorr;
		if (hcrt > mt->HTotal)
			hcrt -= mt->HTotal;
		if (hcrt + 2 > mt->HTotal)
			hcrt = 0;	/* or issue warning? */

		/* last (first? middle?) line in picture can have different length */
		/* hlen - 2 */
		m->regs[0x96] = m->hcorr;
		m->regs[0x97] = m->hcorr >> 8;
		/* ... */
		m->regs[0x98] = 0x00; m->regs[0x99] = 0x00;
		/* hblanking end */
		m->regs[0x9A] = lmargin;	/* 100% */
		m->regs[0x9B] = lmargin >> 8;	/* 100% */
		/* who knows */
		m->regs[0x9C] = 0x04;
		m->regs[0x9D] = 0x00;
		/* htotal - 2 */
		m->regs[0xA0] = m->htotal;
		m->regs[0xA1] = m->htotal >> 8;
		/* vblanking end */
		m->regs[0xA2] = mt->VTotal - mt->VSyncStart - 1;	/* stop vblanking */
		m->regs[0xA3] = (mt->VTotal - mt->VSyncStart - 1) >> 8;
		/* something end... [A6]+1..[A8] */
		if (md->version == MGATVO_B) {
			m->regs[0xA4] = 0x04;
			m->regs[0xA5] = 0x00;
		} else {
			m->regs[0xA4] = 0x01;
			m->regs[0xA5] = 0x00;
		}
		/* something start... 0..[A4]-1 */
		m->regs[0xA6] = 0x00;
		m->regs[0xA7] = 0x00;
		/* vertical line count - 1 */
		m->regs[0xA8] = mt->VTotal - 1;
		m->regs[0xA9] = (mt->VTotal - 1) >> 8;
		/* horizontal vidrst pos */
		m->regs[0xAA] = hcrt;		/* 0 <= hcrt <= htotal - 2 */
		m->regs[0xAB] = hcrt >> 8;
		/* vertical vidrst pos */
		m->regs[0xAC] = mt->VTotal - 2;
		m->regs[0xAD] = (mt->VTotal - 2) >> 8;
		/* moves picture up/down and so on... */
		m->regs[0xAE] = 0x01; /* Fix this... 0..VTotal */
		m->regs[0xAF] = 0x00;
		{
			int hdec;
			int hlen;
			unsigned int ibmin = 4 + lmargin + mt->HDisplay;
			unsigned int ib;
			int i;

			/* Verify! */
			/* Where 94208 came from? */
			if (mt->HTotal)
				hdec = 94208 / (mt->HTotal);
			else
				hdec = 0x81;
			if (hdec > 0x81)
				hdec = 0x81;
			if (hdec < 0x41)
				hdec = 0x41;
			hdec--;
			hlen = 98304 - 128 - ((lmargin + mt->HDisplay - 8) * hdec);
			if (hlen < 0)
				hlen = 0;
			hlen = hlen >> 8;
			if (hlen > 0xFF)
				hlen = 0xFF;
			/* Now we have to compute input buffer length.
			   If you want any picture, it must be between
			     4 + lmargin + xres
			   and
			     94208 / hdec
			   If you want perfect picture even on the top
			   of screen, it must be also
			     0x3C0000 * i / hdec + Q - R / hdec
			   where
			        R      Qmin   Qmax
			     0x07000   0x5AE  0x5BF
			     0x08000   0x5CF  0x5FF
			     0x0C000   0x653  0x67F
			     0x10000   0x6F8  0x6FF
			 */
			i = 1;
			do {
				ib = ((0x3C0000 * i - 0x8000)/ hdec + 0x05E7) >> 8;
				i++;
			} while (ib < ibmin);
			if (ib >= m->htotal + 2) {
				ib = ibmin;
			}

			m->regs[0x90] = hdec;	/* < 0x40 || > 0x80 is bad... 0x80 is questionable */
			m->regs[0xC2] = hlen;
			/* 'valid' input line length */
			m->regs[0x9E] = ib;
			m->regs[0x9F] = ib >> 8;
		}
		{
			int vdec;
			int vlen;

#define MATROX_USE64BIT_DIVIDE
			if (mt->VTotal) {
#ifdef MATROX_USE64BIT_DIVIDE
				u64 f1;
				u32 a;
				u32 b;

				a = m->vlines * (m->htotal + 2);
				b = (mt->VTotal - 1) * (m->htotal + 2) + m->hcorr + 2;

				f1 = ((u64)a) << 15;	/* *32768 */
				do_div(f1, b);
				vdec = f1;
#else
				vdec = m->vlines * 32768 / mt->VTotal;
#endif
			} else
				vdec = 0x8000;
			if (vdec > 0x8000)
				vdec = 0x8000;
			vlen = (vslen + umargin + mt->VDisplay) * vdec;
			vlen = (vlen >> 16) - 146; /* FIXME: 146?! */
			if (vlen < 0)
				vlen = 0;
			if (vlen > 0xFF)
				vlen = 0xFF;
			vdec--;
			m->regs[0x91] = vdec;
			m->regs[0x92] = vdec >> 8;
			m->regs[0xBE] = vlen;
		}
		m->regs[0xB0] = 0x08;	/* output: SVideo/Composite */
		return 0;
	}

	DAC1064_calcclock(mt->pixclock, 450000, &a, &bv, &c);
	m->regs[0x80] = a;
	m->regs[0x81] = bv;
	m->regs[0x82] = c | 0x80;

	m->regs[0xB3] = 0x01;
	m->regs[0x94] = 0xB2;

	/* htotal... */
	m->regs[0x96] = mt->HTotal;
	m->regs[0x97] = mt->HTotal >> 8;
	/* ?? */
	m->regs[0x98] = 0x00;
	m->regs[0x99] = 0x00;
	/* hsync len */
	tmpi = mt->HSyncEnd - mt->HSyncStart;
	m->regs[0x9A] = tmpi;
	m->regs[0x9B] = tmpi >> 8;
	/* hblank end */
	tmpi = mt->HTotal - mt->HSyncStart;
	m->regs[0x9C] = tmpi;
	m->regs[0x9D] = tmpi >> 8;
	/* hblank start */
	tmpi += mt->HDisplay;
	m->regs[0x9E] = tmpi;
	m->regs[0x9F] = tmpi >> 8;
	/* htotal + 1 */
	tmpi = mt->HTotal + 1;
	m->regs[0xA0] = tmpi;
	m->regs[0xA1] = tmpi >> 8;
	/* vsync?! */
	tmpi = mt->VSyncEnd - mt->VSyncStart - 1;
	m->regs[0xA2] = tmpi;
	m->regs[0xA3] = tmpi >> 8;
	/* ignored? */
	tmpi = mt->VTotal - mt->VSyncStart;
	m->regs[0xA4] = tmpi;
	m->regs[0xA5] = tmpi >> 8;
	/* ignored? */
	tmpi = mt->VTotal - 1;
	m->regs[0xA6] = tmpi;
	m->regs[0xA7] = tmpi >> 8;
	/* vtotal - 1 */
	m->regs[0xA8] = tmpi;
	m->regs[0xA9] = tmpi >> 8;
	/* hor vidrst */
	tmpi = mt->HTotal - mt->delay;
	m->regs[0xAA] = tmpi;
	m->regs[0xAB] = tmpi >> 8;
	/* vert vidrst */
	tmpi = mt->VTotal - 2;
	m->regs[0xAC] = tmpi;
	m->regs[0xAD] = tmpi >> 8;
	/* ignored? */
	m->regs[0xAE] = 0x00;
	m->regs[0xAF] = 0x00;

	m->regs[0xB0] = 0x03;	/* output: monitor */
	m->regs[0xB1] = 0xA0;	/* ??? */
	m->regs[0x8C] = 0x20;	/* must be set... */
	m->regs[0x8D] = 0x04;	/* defaults to 0x10: test signal */
	m->regs[0xB9] = 0x1A;	/* defaults to 0x2C: too bright */
	m->regs[0xBF] = 0x22;	/* makes picture stable */

	return 0;
}