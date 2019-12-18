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
typedef  int v4l2_std_id ;
typedef  long u64 ;
typedef  long u32 ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; int vbi_line_offset; scalar_t__ generic_mode; } ;

/* Variables and functions */
 int V4L2_STD_625_50 ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  cx25840_debug ; 
 long cx25840_read (struct i2c_client*,int) ; 
 int cx25840_read4 (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  is_cx231xx (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int,...) ; 

void cx25840_std_setup(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	v4l2_std_id std = state->std;
	int hblank, hactive, burst, vblank, vactive, sc;
	int vblank656, src_decimation;
	int luma_lpf, uv_lpf, comb;
	u32 pll_int, pll_frac, pll_post;

	/* datasheet startup, step 8d */
	if (std & ~V4L2_STD_NTSC)
		cx25840_write(client, 0x49f, 0x11);
	else
		cx25840_write(client, 0x49f, 0x14);

	/* generic mode uses the values that the chip autoconfig would set */
	if (std & V4L2_STD_625_50) {
		hblank = 132;
		hactive = 720;
		burst = 93;
		if (state->generic_mode) {
			vblank = 34;
			vactive = 576;
			vblank656 = 38;
		} else {
			vblank = 36;
			vactive = 580;
			vblank656 = 40;
		}
		src_decimation = 0x21f;
		luma_lpf = 2;

		if (std & V4L2_STD_SECAM) {
			uv_lpf = 0;
			comb = 0;
			sc = 0x0a425f;
		} else if (std == V4L2_STD_PAL_Nc) {
			if (state->generic_mode) {
				burst = 95;
				luma_lpf = 1;
			}
			uv_lpf = 1;
			comb = 0x20;
			sc = 556453;
		} else {
			uv_lpf = 1;
			comb = 0x20;
			sc = 688739;
		}
	} else {
		hactive = 720;
		hblank = 122;
		vactive = 487;
		luma_lpf = 1;
		uv_lpf = 1;
		if (state->generic_mode) {
			vblank = 20;
			vblank656 = 24;
		}

		src_decimation = 0x21f;
		if (std == V4L2_STD_PAL_60) {
			if (!state->generic_mode) {
				vblank = 26;
				vblank656 = 26;
				burst = 0x5b;
			} else {
				burst = 0x59;
			}
			luma_lpf = 2;
			comb = 0x20;
			sc = 688739;
		} else if (std == V4L2_STD_PAL_M) {
			vblank = 20;
			vblank656 = 24;
			burst = 0x61;
			comb = 0x20;
			sc = 555452;
		} else {
			if (!state->generic_mode) {
				vblank = 26;
				vblank656 = 26;
			}
			burst = 0x5b;
			comb = 0x66;
			sc = 556063;
		}
	}

	/* DEBUG: Displays configured PLL frequency */
	if (!is_cx231xx(state)) {
		pll_int = cx25840_read(client, 0x108);
		pll_frac = cx25840_read4(client, 0x10c) & 0x1ffffff;
		pll_post = cx25840_read(client, 0x109);
		v4l_dbg(1, cx25840_debug, client,
			"PLL regs = int: %u, frac: %u, post: %u\n",
			pll_int, pll_frac, pll_post);

		if (pll_post) {
			int fin, fsc;
			int pll = (28636363L * ((((u64)pll_int) << 25L) + pll_frac)) >> 25L;

			pll /= pll_post;
			v4l_dbg(1, cx25840_debug, client,
				"PLL = %d.%06d MHz\n",
				pll / 1000000, pll % 1000000);
			v4l_dbg(1, cx25840_debug, client,
				"PLL/8 = %d.%06d MHz\n",
				pll / 8000000, (pll / 8) % 1000000);

			fin = ((u64)src_decimation * pll) >> 12;
			v4l_dbg(1, cx25840_debug, client,
				"ADC Sampling freq = %d.%06d MHz\n",
				fin / 1000000, fin % 1000000);

			fsc = (((u64)sc) * pll) >> 24L;
			v4l_dbg(1, cx25840_debug, client,
				"Chroma sub-carrier freq = %d.%06d MHz\n",
				fsc / 1000000, fsc % 1000000);

			v4l_dbg(1, cx25840_debug, client,
				"hblank %i, hactive %i, vblank %i, vactive %i, vblank656 %i, src_dec %i, burst 0x%02x, luma_lpf %i, uv_lpf %i, comb 0x%02x, sc 0x%06x\n",
				hblank, hactive, vblank, vactive, vblank656,
				src_decimation, burst, luma_lpf, uv_lpf,
				comb, sc);
		}
	}

	/* Sets horizontal blanking delay and active lines */
	cx25840_write(client, 0x470, hblank);
	cx25840_write(client, 0x471,
		      (((hblank >> 8) & 0x3) | (hactive << 4)) & 0xff);
	cx25840_write(client, 0x472, hactive >> 4);

	/* Sets burst gate delay */
	cx25840_write(client, 0x473, burst);

	/* Sets vertical blanking delay and active duration */
	cx25840_write(client, 0x474, vblank);
	cx25840_write(client, 0x475,
		      (((vblank >> 8) & 0x3) | (vactive << 4)) & 0xff);
	cx25840_write(client, 0x476, vactive >> 4);
	cx25840_write(client, 0x477, vblank656);

	/* Sets src decimation rate */
	cx25840_write(client, 0x478, src_decimation & 0xff);
	cx25840_write(client, 0x479, (src_decimation >> 8) & 0xff);

	/* Sets Luma and UV Low pass filters */
	cx25840_write(client, 0x47a, luma_lpf << 6 | ((uv_lpf << 4) & 0x30));

	/* Enables comb filters */
	cx25840_write(client, 0x47b, comb);

	/* Sets SC Step*/
	cx25840_write(client, 0x47c, sc);
	cx25840_write(client, 0x47d, (sc >> 8) & 0xff);
	cx25840_write(client, 0x47e, (sc >> 16) & 0xff);

	/* Sets VBI parameters */
	if (std & V4L2_STD_625_50) {
		cx25840_write(client, 0x47f, 0x01);
		state->vbi_line_offset = 5;
	} else {
		cx25840_write(client, 0x47f, 0x00);
		state->vbi_line_offset = 8;
	}
}