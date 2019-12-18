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
struct pm2fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_RD_PALETTE_DATA ; 
 int /*<<< orphan*/  PM2R_RD_PALETTE_WRITE_ADDRESS ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void set_color(struct pm2fb_par *p, unsigned char regno,
		      unsigned char r, unsigned char g, unsigned char b)
{
	WAIT_FIFO(p, 4);
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, regno);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, r);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, g);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, b);
}