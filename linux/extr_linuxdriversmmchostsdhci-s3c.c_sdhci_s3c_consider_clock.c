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
struct sdhci_s3c {unsigned long* clk_rates; TYPE_1__* pdev; scalar_t__ no_divider; struct clk** clk_bus; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 unsigned int UINT_MAX ; 
 unsigned long clk_round_rate (struct clk*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned long,unsigned int,unsigned long) ; 

__attribute__((used)) static unsigned int sdhci_s3c_consider_clock(struct sdhci_s3c *ourhost,
					     unsigned int src,
					     unsigned int wanted)
{
	unsigned long rate;
	struct clk *clksrc = ourhost->clk_bus[src];
	int shift;

	if (IS_ERR(clksrc))
		return UINT_MAX;

	/*
	 * If controller uses a non-standard clock division, find the best clock
	 * speed possible with selected clock source and skip the division.
	 */
	if (ourhost->no_divider) {
		rate = clk_round_rate(clksrc, wanted);
		return wanted - rate;
	}

	rate = ourhost->clk_rates[src];

	for (shift = 0; shift <= 8; ++shift) {
		if ((rate >> shift) <= wanted)
			break;
	}

	if (shift > 8) {
		dev_dbg(&ourhost->pdev->dev,
			"clk %d: rate %ld, min rate %lu > wanted %u\n",
			src, rate, rate / 256, wanted);
		return UINT_MAX;
	}

	dev_dbg(&ourhost->pdev->dev, "clk %d: rate %ld, want %d, got %ld\n",
		src, rate, wanted, rate >> shift);

	return wanted - (rate >> shift);
}