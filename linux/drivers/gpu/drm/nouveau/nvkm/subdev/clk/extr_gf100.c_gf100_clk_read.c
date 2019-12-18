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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int crystal; } ;
struct nvkm_clk {int dummy; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct gf100_clk {TYPE_1__ base; } ;
typedef  enum nv_clk_src { ____Placeholder_nv_clk_src } nv_clk_src ;

/* Variables and functions */
 int EINVAL ; 
 struct gf100_clk* gf100_clk (struct nvkm_clk*) ; 
#define  nv_clk_src_copy 144 
#define  nv_clk_src_crystal 143 
#define  nv_clk_src_gpc 142 
#define  nv_clk_src_href 141 
#define  nv_clk_src_hubk01 140 
#define  nv_clk_src_hubk06 139 
#define  nv_clk_src_hubk07 138 
#define  nv_clk_src_mdiv 137 
#define  nv_clk_src_mem 136 
#define  nv_clk_src_mpll 135 
#define  nv_clk_src_mpllsrc 134 
#define  nv_clk_src_mpllsrcref 133 
#define  nv_clk_src_pmu 132 
#define  nv_clk_src_rop 131 
#define  nv_clk_src_sppll0 130 
#define  nv_clk_src_sppll1 129 
#define  nv_clk_src_vdec 128 
 int nvkm_clk_read (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_clk (struct gf100_clk*,int) ; 
 int read_div (struct gf100_clk*,int /*<<< orphan*/ ,int,int) ; 
 int read_pll (struct gf100_clk*,int) ; 

__attribute__((used)) static int
gf100_clk_read(struct nvkm_clk *base, enum nv_clk_src src)
{
	struct gf100_clk *clk = gf100_clk(base);
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;

	switch (src) {
	case nv_clk_src_crystal:
		return device->crystal;
	case nv_clk_src_href:
		return 100000;
	case nv_clk_src_sppll0:
		return read_pll(clk, 0x00e800);
	case nv_clk_src_sppll1:
		return read_pll(clk, 0x00e820);

	case nv_clk_src_mpllsrcref:
		return read_div(clk, 0, 0x137320, 0x137330);
	case nv_clk_src_mpllsrc:
		return read_pll(clk, 0x132020);
	case nv_clk_src_mpll:
		return read_pll(clk, 0x132000);
	case nv_clk_src_mdiv:
		return read_div(clk, 0, 0x137300, 0x137310);
	case nv_clk_src_mem:
		if (nvkm_rd32(device, 0x1373f0) & 0x00000002)
			return nvkm_clk_read(&clk->base, nv_clk_src_mpll);
		return nvkm_clk_read(&clk->base, nv_clk_src_mdiv);

	case nv_clk_src_gpc:
		return read_clk(clk, 0x00);
	case nv_clk_src_rop:
		return read_clk(clk, 0x01);
	case nv_clk_src_hubk07:
		return read_clk(clk, 0x02);
	case nv_clk_src_hubk06:
		return read_clk(clk, 0x07);
	case nv_clk_src_hubk01:
		return read_clk(clk, 0x08);
	case nv_clk_src_copy:
		return read_clk(clk, 0x09);
	case nv_clk_src_pmu:
		return read_clk(clk, 0x0c);
	case nv_clk_src_vdec:
		return read_clk(clk, 0x0e);
	default:
		nvkm_error(subdev, "invalid clock source %d\n", src);
		return -EINVAL;
	}
}