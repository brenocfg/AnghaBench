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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int chipset; } ;
struct nvkm_cstate {int* domain; } ;
struct nvkm_clk {int dummy; } ;
struct nv50_clk_hwsq {int dummy; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nv50_clk {TYPE_1__ base; struct nv50_clk_hwsq hwsq; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ abs (int const) ; 
 int calc_div (int const,int const,int*) ; 
 int calc_pll (struct nv50_clk*,int,int const,int*,int*,int*) ; 
 int clk_init (struct nv50_clk_hwsq*,struct nvkm_subdev*) ; 
 int /*<<< orphan*/  clk_mask (struct nv50_clk_hwsq*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clk_nsec (struct nv50_clk_hwsq*,int) ; 
 scalar_t__ clk_same (int const,int) ; 
 int /*<<< orphan*/  clk_setf (struct nv50_clk_hwsq*,int,int) ; 
 int /*<<< orphan*/  clk_wait (struct nv50_clk_hwsq*,int,int) ; 
 int /*<<< orphan*/  clk_wr32 (struct nv50_clk_hwsq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  divs ; 
 int /*<<< orphan*/  fifo ; 
 int /*<<< orphan*/  mast ; 
 struct nv50_clk* nv50_clk (struct nvkm_clk*) ; 
 size_t nv_clk_src_core ; 
 size_t nv_clk_src_dom6 ; 
 int /*<<< orphan*/  nv_clk_src_hclk ; 
 int /*<<< orphan*/  nv_clk_src_hclkm3d2 ; 
 int /*<<< orphan*/  nv_clk_src_href ; 
 size_t nv_clk_src_shader ; 
 size_t nv_clk_src_vdec ; 
 int nvkm_clk_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpll ; 
 int read_pll (struct nv50_clk*,int) ; 
 int /*<<< orphan*/ * spll ; 

int
nv50_clk_calc(struct nvkm_clk *base, struct nvkm_cstate *cstate)
{
	struct nv50_clk *clk = nv50_clk(base);
	struct nv50_clk_hwsq *hwsq = &clk->hwsq;
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	const int shader = cstate->domain[nv_clk_src_shader];
	const int core = cstate->domain[nv_clk_src_core];
	const int vdec = cstate->domain[nv_clk_src_vdec];
	const int dom6 = cstate->domain[nv_clk_src_dom6];
	u32 mastm = 0, mastv = 0;
	u32 divsm = 0, divsv = 0;
	int N, M, P1, P2;
	int freq, out;

	/* prepare a hwsq script from which we'll perform the reclock */
	out = clk_init(hwsq, subdev);
	if (out)
		return out;

	clk_wr32(hwsq, fifo, 0x00000001); /* block fifo */
	clk_nsec(hwsq, 8000);
	clk_setf(hwsq, 0x10, 0x00); /* disable fb */
	clk_wait(hwsq, 0x00, 0x01); /* wait for fb disabled */

	/* vdec: avoid modifying xpll until we know exactly how the other
	 * clock domains work, i suspect at least some of them can also be
	 * tied to xpll...
	 */
	if (vdec) {
		/* see how close we can get using nvclk as a source */
		freq = calc_div(core, vdec, &P1);

		/* see how close we can get using xpll/hclk as a source */
		if (device->chipset != 0x98)
			out = read_pll(clk, 0x004030);
		else
			out = nvkm_clk_read(&clk->base, nv_clk_src_hclkm3d2);
		out = calc_div(out, vdec, &P2);

		/* select whichever gets us closest */
		if (abs(vdec - freq) <= abs(vdec - out)) {
			if (device->chipset != 0x98)
				mastv |= 0x00000c00;
			divsv |= P1 << 8;
		} else {
			mastv |= 0x00000800;
			divsv |= P2 << 8;
		}

		mastm |= 0x00000c00;
		divsm |= 0x00000700;
	}

	/* dom6: nfi what this is, but we're limited to various combinations
	 * of the host clock frequency
	 */
	if (dom6) {
		if (clk_same(dom6, nvkm_clk_read(&clk->base, nv_clk_src_href))) {
			mastv |= 0x00000000;
		} else
		if (clk_same(dom6, nvkm_clk_read(&clk->base, nv_clk_src_hclk))) {
			mastv |= 0x08000000;
		} else {
			freq = nvkm_clk_read(&clk->base, nv_clk_src_hclk) * 3;
			calc_div(freq, dom6, &P1);

			mastv |= 0x0c000000;
			divsv |= P1;
		}

		mastm |= 0x0c000000;
		divsm |= 0x00000007;
	}

	/* vdec/dom6: switch to "safe" clocks temporarily, update dividers
	 * and then switch to target clocks
	 */
	clk_mask(hwsq, mast, mastm, 0x00000000);
	clk_mask(hwsq, divs, divsm, divsv);
	clk_mask(hwsq, mast, mastm, mastv);

	/* core/shader: disconnect nvclk/sclk from their PLLs (nvclk to dom6,
	 * sclk to hclk) before reprogramming
	 */
	if (device->chipset < 0x92)
		clk_mask(hwsq, mast, 0x001000b0, 0x00100080);
	else
		clk_mask(hwsq, mast, 0x000000b3, 0x00000081);

	/* core: for the moment at least, always use nvpll */
	freq = calc_pll(clk, 0x4028, core, &N, &M, &P1);
	if (freq == 0)
		return -ERANGE;

	clk_mask(hwsq, nvpll[0], 0xc03f0100,
				 0x80000000 | (P1 << 19) | (P1 << 16));
	clk_mask(hwsq, nvpll[1], 0x0000ffff, (N << 8) | M);

	/* shader: tie to nvclk if possible, otherwise use spll.  have to be
	 * very careful that the shader clock is at least twice the core, or
	 * some chipsets will be very unhappy.  i expect most or all of these
	 * cases will be handled by tying to nvclk, but it's possible there's
	 * corners
	 */
	if (P1-- && shader == (core << 1)) {
		clk_mask(hwsq, spll[0], 0xc03f0100, (P1 << 19) | (P1 << 16));
		clk_mask(hwsq, mast, 0x00100033, 0x00000023);
	} else {
		freq = calc_pll(clk, 0x4020, shader, &N, &M, &P1);
		if (freq == 0)
			return -ERANGE;

		clk_mask(hwsq, spll[0], 0xc03f0100,
					0x80000000 | (P1 << 19) | (P1 << 16));
		clk_mask(hwsq, spll[1], 0x0000ffff, (N << 8) | M);
		clk_mask(hwsq, mast, 0x00100033, 0x00000033);
	}

	/* restore normal operation */
	clk_setf(hwsq, 0x10, 0x01); /* enable fb */
	clk_wait(hwsq, 0x00, 0x00); /* wait for fb enabled */
	clk_wr32(hwsq, fifo, 0x00000000); /* un-block fifo */
	return 0;
}