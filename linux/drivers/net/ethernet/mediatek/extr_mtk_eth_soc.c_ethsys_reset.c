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
struct mtk_eth {int /*<<< orphan*/  ethsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHSYS_RSTCTRL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ethsys_reset(struct mtk_eth *eth, u32 reset_bits)
{
	regmap_update_bits(eth->ethsys, ETHSYS_RSTCTRL,
			   reset_bits,
			   reset_bits);

	usleep_range(1000, 1100);
	regmap_update_bits(eth->ethsys, ETHSYS_RSTCTRL,
			   reset_bits,
			   ~reset_bits);
	mdelay(10);
}