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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* bw; } ;
struct dib7000p_state {TYPE_2__ cfg; } ;
typedef  int s16 ;
struct TYPE_3__ {int xtal_hz; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 

__attribute__((used)) static void dib7000p_spur_protect(struct dib7000p_state *state, u32 rf_khz, u32 bw)
{
	static s16 notch[] = { 16143, 14402, 12238, 9713, 6902, 3888, 759, -2392 };
	static u8 sine[] = { 0, 2, 3, 5, 6, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22,
		24, 25, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51,
		53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80,
		82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 97, 98, 99, 101, 102, 104, 105,
		107, 108, 109, 111, 112, 114, 115, 117, 118, 119, 121, 122, 123, 125, 126,
		128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 144, 145, 146,
		147, 149, 150, 151, 152, 154, 155, 156, 157, 159, 160, 161, 162, 164, 165,
		166, 167, 168, 170, 171, 172, 173, 174, 175, 177, 178, 179, 180, 181, 182,
		183, 184, 185, 186, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198,
		199, 200, 201, 202, 203, 204, 205, 206, 207, 207, 208, 209, 210, 211, 212,
		213, 214, 215, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 224,
		225, 226, 227, 227, 228, 229, 229, 230, 231, 231, 232, 233, 233, 234, 235,
		235, 236, 237, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243,
		244, 244, 245, 245, 245, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249,
		250, 250, 250, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 254,
		254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255
	};

	u32 xtal = state->cfg.bw->xtal_hz / 1000;
	int f_rel = DIV_ROUND_CLOSEST(rf_khz, xtal) * xtal - rf_khz;
	int k;
	int coef_re[8], coef_im[8];
	int bw_khz = bw;
	u32 pha;

	dprintk("relative position of the Spur: %dk (RF: %dk, XTAL: %dk)\n", f_rel, rf_khz, xtal);

	if (f_rel < -bw_khz / 2 || f_rel > bw_khz / 2)
		return;

	bw_khz /= 100;

	dib7000p_write_word(state, 142, 0x0610);

	for (k = 0; k < 8; k++) {
		pha = ((f_rel * (k + 1) * 112 * 80 / bw_khz) / 1000) & 0x3ff;

		if (pha == 0) {
			coef_re[k] = 256;
			coef_im[k] = 0;
		} else if (pha < 256) {
			coef_re[k] = sine[256 - (pha & 0xff)];
			coef_im[k] = sine[pha & 0xff];
		} else if (pha == 256) {
			coef_re[k] = 0;
			coef_im[k] = 256;
		} else if (pha < 512) {
			coef_re[k] = -sine[pha & 0xff];
			coef_im[k] = sine[256 - (pha & 0xff)];
		} else if (pha == 512) {
			coef_re[k] = -256;
			coef_im[k] = 0;
		} else if (pha < 768) {
			coef_re[k] = -sine[256 - (pha & 0xff)];
			coef_im[k] = -sine[pha & 0xff];
		} else if (pha == 768) {
			coef_re[k] = 0;
			coef_im[k] = -256;
		} else {
			coef_re[k] = sine[pha & 0xff];
			coef_im[k] = -sine[256 - (pha & 0xff)];
		}

		coef_re[k] *= notch[k];
		coef_re[k] += (1 << 14);
		if (coef_re[k] >= (1 << 24))
			coef_re[k] = (1 << 24) - 1;
		coef_re[k] /= (1 << 15);

		coef_im[k] *= notch[k];
		coef_im[k] += (1 << 14);
		if (coef_im[k] >= (1 << 24))
			coef_im[k] = (1 << 24) - 1;
		coef_im[k] /= (1 << 15);

		dprintk("PALF COEF: %d re: %d im: %d\n", k, coef_re[k], coef_im[k]);

		dib7000p_write_word(state, 143, (0 << 14) | (k << 10) | (coef_re[k] & 0x3ff));
		dib7000p_write_word(state, 144, coef_im[k] & 0x3ff);
		dib7000p_write_word(state, 143, (1 << 14) | (k << 10) | (coef_re[k] & 0x3ff));
	}
	dib7000p_write_word(state, 143, 0);
}