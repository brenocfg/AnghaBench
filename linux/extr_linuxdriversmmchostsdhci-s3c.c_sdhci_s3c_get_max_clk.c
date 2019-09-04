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
struct sdhci_s3c {unsigned long* clk_rates; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int MAX_BUS_CLK ; 
 struct sdhci_s3c* to_s3c (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int sdhci_s3c_get_max_clk(struct sdhci_host *host)
{
	struct sdhci_s3c *ourhost = to_s3c(host);
	unsigned long rate, max = 0;
	int src;

	for (src = 0; src < MAX_BUS_CLK; src++) {
		rate = ourhost->clk_rates[src];
		if (rate > max)
			max = rate;
	}

	return max;
}