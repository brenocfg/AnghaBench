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
struct mtk_eth {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PHY_IAC ; 
 int PHY_IAC_ACCESS ; 
 scalar_t__ PHY_IAC_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mtk_mdio_busy_wait(struct mtk_eth *eth)
{
	unsigned long t_start = jiffies;

	while (1) {
		if (!(mtk_r32(eth, MTK_PHY_IAC) & PHY_IAC_ACCESS))
			return 0;
		if (time_after(jiffies, t_start + PHY_IAC_TIMEOUT))
			break;
		usleep_range(10, 20);
	}

	dev_err(eth->dev, "mdio: MDIO timeout\n");
	return -1;
}