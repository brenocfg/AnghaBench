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
typedef  int u32 ;
struct nvkm_clk {int dummy; } ;
struct gt215_clk_info {int /*<<< orphan*/  clk; } ;
struct gt215_clk {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int ERANGE ; 
 struct gt215_clk* gt215_clk (struct nvkm_clk*) ; 
 int min (int,int) ; 
 int read_vco (struct gt215_clk*,int) ; 

__attribute__((used)) static int
gt215_clk_info(struct nvkm_clk *base, int idx, u32 khz,
	       struct gt215_clk_info *info)
{
	struct gt215_clk *clk = gt215_clk(base);
	u32 oclk, sclk, sdiv;
	s32 diff;

	info->clk = 0;

	switch (khz) {
	case 27000:
		info->clk = 0x00000100;
		return khz;
	case 100000:
		info->clk = 0x00002100;
		return khz;
	case 108000:
		info->clk = 0x00002140;
		return khz;
	default:
		sclk = read_vco(clk, idx);
		sdiv = min((sclk * 2) / khz, (u32)65);
		oclk = (sclk * 2) / sdiv;
		diff = ((khz + 3000) - oclk);

		/* When imprecise, play it safe and aim for a clock lower than
		 * desired rather than higher */
		if (diff < 0) {
			sdiv++;
			oclk = (sclk * 2) / sdiv;
		}

		/* divider can go as low as 2, limited here because NVIDIA
		 * and the VBIOS on my NVA8 seem to prefer using the PLL
		 * for 810MHz - is there a good reason?
		 * XXX: PLLs with refclk 810MHz?  */
		if (sdiv > 4) {
			info->clk = (((sdiv - 2) << 16) | 0x00003100);
			return oclk;
		}

		break;
	}

	return -ERANGE;
}