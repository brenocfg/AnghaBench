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
struct pm2fb_par {int type; } ;

/* Variables and functions */
 int PM2F_PLL_LOCKED ; 
 int /*<<< orphan*/  PM2I_RD_MEMORY_CLOCK_1 ; 
 int /*<<< orphan*/  PM2I_RD_MEMORY_CLOCK_2 ; 
 int /*<<< orphan*/  PM2I_RD_MEMORY_CLOCK_3 ; 
 int /*<<< orphan*/  PM2I_RD_MEMORY_CLOCK_STATUS ; 
 int /*<<< orphan*/  PM2R_RD_INDEXED_DATA ; 
 int PM2VI_RD_MCLK_CONTROL ; 
 int PM2VI_RD_MCLK_FEEDBACK ; 
 int PM2VI_RD_MCLK_POSTSCALE ; 
 int PM2VI_RD_MCLK_PRESCALE ; 
 int /*<<< orphan*/  PM2VR_RD_INDEX_HIGH ; 
#define  PM2_TYPE_PERMEDIA2 129 
#define  PM2_TYPE_PERMEDIA2V 128 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int pm2_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_RDAC_RD (struct pm2fb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm2_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2_mnp (int,unsigned char*,unsigned char*,unsigned char*) ; 
 int pm2v_RDAC_RD (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2v_RDAC_WR (struct pm2fb_par*,int,int) ; 
 int /*<<< orphan*/  pm2v_mnp (int,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void set_memclock(struct pm2fb_par *par, u32 clk)
{
	int i;
	unsigned char m, n, p;

	switch (par->type) {
	case PM2_TYPE_PERMEDIA2V:
		pm2v_mnp(clk/2, &m, &n, &p);
		WAIT_FIFO(par, 12);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, PM2VI_RD_MCLK_CONTROL >> 8);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_CONTROL, 0);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_PRESCALE, m);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_FEEDBACK, n);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_POSTSCALE, p);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_CONTROL, 1);
		rmb();
		for (i = 256; i; i--)
			if (pm2v_RDAC_RD(par, PM2VI_RD_MCLK_CONTROL) & 2)
				break;
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
		break;
	case PM2_TYPE_PERMEDIA2:
		pm2_mnp(clk, &m, &n, &p);
		WAIT_FIFO(par, 10);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_3, 6);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_1, m);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_2, n);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_3, 8|p);
		pm2_RDAC_RD(par, PM2I_RD_MEMORY_CLOCK_STATUS);
		rmb();
		for (i = 256; i; i--)
			if (pm2_RD(par, PM2R_RD_INDEXED_DATA) & PM2F_PLL_LOCKED)
				break;
		break;
	}
}