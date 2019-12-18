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
struct sdhci_s3c {struct clk** clk_bus; } ;
struct sdhci_host {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int MAX_BUS_CLK ; 
 unsigned long ULONG_MAX ; 
 unsigned long clk_round_rate (struct clk*,int /*<<< orphan*/ ) ; 
 struct sdhci_s3c* to_s3c (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int sdhci_cmu_get_min_clock(struct sdhci_host *host)
{
	struct sdhci_s3c *ourhost = to_s3c(host);
	unsigned long rate, min = ULONG_MAX;
	int src;

	for (src = 0; src < MAX_BUS_CLK; src++) {
		struct clk *clk;

		clk = ourhost->clk_bus[src];
		if (IS_ERR(clk))
			continue;

		rate = clk_round_rate(clk, 0);
		if (rate < min)
			min = rate;
	}

	return min;
}