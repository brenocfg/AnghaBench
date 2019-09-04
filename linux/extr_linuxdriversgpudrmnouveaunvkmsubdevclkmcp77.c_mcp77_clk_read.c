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
struct nvkm_device {int crystal; } ;
struct nvkm_clk {int dummy; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct mcp77_clk {TYPE_1__ base; } ;
typedef  enum nv_clk_src { ____Placeholder_nv_clk_src } nv_clk_src ;

/* Variables and functions */
 struct mcp77_clk* mcp77_clk (struct nvkm_clk*) ; 
#define  nv_clk_src_cclk 137 
#define  nv_clk_src_core 136 
#define  nv_clk_src_crystal 135 
#define  nv_clk_src_hclkm2d3 134 
#define  nv_clk_src_hclkm4 133 
#define  nv_clk_src_host 132 
#define  nv_clk_src_href 131 
#define  nv_clk_src_mem 130 
#define  nv_clk_src_shader 129 
#define  nv_clk_src_vdec 128 
 int nvkm_clk_read (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_div (struct mcp77_clk*) ; 
 int read_pll (struct mcp77_clk*,int) ; 

__attribute__((used)) static int
mcp77_clk_read(struct nvkm_clk *base, enum nv_clk_src src)
{
	struct mcp77_clk *clk = mcp77_clk(base);
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	u32 mast = nvkm_rd32(device, 0x00c054);
	u32 P = 0;

	switch (src) {
	case nv_clk_src_crystal:
		return device->crystal;
	case nv_clk_src_href:
		return 100000; /* PCIE reference clock */
	case nv_clk_src_hclkm4:
		return nvkm_clk_read(&clk->base, nv_clk_src_href) * 4;
	case nv_clk_src_hclkm2d3:
		return nvkm_clk_read(&clk->base, nv_clk_src_href) * 2 / 3;
	case nv_clk_src_host:
		switch (mast & 0x000c0000) {
		case 0x00000000: return nvkm_clk_read(&clk->base, nv_clk_src_hclkm2d3);
		case 0x00040000: break;
		case 0x00080000: return nvkm_clk_read(&clk->base, nv_clk_src_hclkm4);
		case 0x000c0000: return nvkm_clk_read(&clk->base, nv_clk_src_cclk);
		}
		break;
	case nv_clk_src_core:
		P = (nvkm_rd32(device, 0x004028) & 0x00070000) >> 16;

		switch (mast & 0x00000003) {
		case 0x00000000: return nvkm_clk_read(&clk->base, nv_clk_src_crystal) >> P;
		case 0x00000001: return 0;
		case 0x00000002: return nvkm_clk_read(&clk->base, nv_clk_src_hclkm4) >> P;
		case 0x00000003: return read_pll(clk, 0x004028) >> P;
		}
		break;
	case nv_clk_src_cclk:
		if ((mast & 0x03000000) != 0x03000000)
			return nvkm_clk_read(&clk->base, nv_clk_src_core);

		if ((mast & 0x00000200) == 0x00000000)
			return nvkm_clk_read(&clk->base, nv_clk_src_core);

		switch (mast & 0x00000c00) {
		case 0x00000000: return nvkm_clk_read(&clk->base, nv_clk_src_href);
		case 0x00000400: return nvkm_clk_read(&clk->base, nv_clk_src_hclkm4);
		case 0x00000800: return nvkm_clk_read(&clk->base, nv_clk_src_hclkm2d3);
		default: return 0;
		}
	case nv_clk_src_shader:
		P = (nvkm_rd32(device, 0x004020) & 0x00070000) >> 16;
		switch (mast & 0x00000030) {
		case 0x00000000:
			if (mast & 0x00000040)
				return nvkm_clk_read(&clk->base, nv_clk_src_href) >> P;
			return nvkm_clk_read(&clk->base, nv_clk_src_crystal) >> P;
		case 0x00000010: break;
		case 0x00000020: return read_pll(clk, 0x004028) >> P;
		case 0x00000030: return read_pll(clk, 0x004020) >> P;
		}
		break;
	case nv_clk_src_mem:
		return 0;
		break;
	case nv_clk_src_vdec:
		P = (read_div(clk) & 0x00000700) >> 8;

		switch (mast & 0x00400000) {
		case 0x00400000:
			return nvkm_clk_read(&clk->base, nv_clk_src_core) >> P;
			break;
		default:
			return 500000 >> P;
			break;
		}
		break;
	default:
		break;
	}

	nvkm_debug(subdev, "unknown clock source %d %08x\n", src, mast);
	return 0;
}