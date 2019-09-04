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
typedef  int /*<<< orphan*/  u32 ;
struct a10_fpga_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_FPGAMGR_DCLKCNT_OFST ; 
 int /*<<< orphan*/  A10_FPGAMGR_DCLKSTAT_DCLKDONE ; 
 int /*<<< orphan*/  A10_FPGAMGR_DCLKSTAT_OFST ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socfpga_a10_fpga_generate_dclks(struct a10_fpga_priv *priv,
					    u32 count)
{
	u32 val;

	/* Clear any existing DONE status. */
	regmap_write(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST,
		     A10_FPGAMGR_DCLKSTAT_DCLKDONE);

	/* Issue the DCLK regmap. */
	regmap_write(priv->regmap, A10_FPGAMGR_DCLKCNT_OFST, count);

	/* wait till the dclkcnt done */
	regmap_read_poll_timeout(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST, val,
				 val, 1, 100);

	/* Clear DONE status. */
	regmap_write(priv->regmap, A10_FPGAMGR_DCLKSTAT_OFST,
		     A10_FPGAMGR_DCLKSTAT_DCLKDONE);
}