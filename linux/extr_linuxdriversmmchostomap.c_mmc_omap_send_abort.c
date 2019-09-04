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
typedef  int u16 ;
struct mmc_omap_slot {int /*<<< orphan*/  fclk_freq; } ;
struct mmc_omap_host {struct mmc_omap_slot* current_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 unsigned int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int OMAP_MMC_STAT_END_OF_CMD ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAT ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mmc_omap_send_abort(struct mmc_omap_host *host, int maxloops)
{
	struct mmc_omap_slot *slot = host->current_slot;
	unsigned int restarts, passes, timeout;
	u16 stat = 0;

	/* Sending abort takes 80 clocks. Have some extra and round up */
	timeout = DIV_ROUND_UP(120 * USEC_PER_SEC, slot->fclk_freq);
	restarts = 0;
	while (restarts < maxloops) {
		OMAP_MMC_WRITE(host, STAT, 0xFFFF);
		OMAP_MMC_WRITE(host, CMD, (3 << 12) | (1 << 7));

		passes = 0;
		while (passes < timeout) {
			stat = OMAP_MMC_READ(host, STAT);
			if (stat & OMAP_MMC_STAT_END_OF_CMD)
				goto out;
			udelay(1);
			passes++;
		}

		restarts++;
	}
out:
	OMAP_MMC_WRITE(host, STAT, stat);
}