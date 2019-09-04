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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ a6xx_gmu_get_arc_level (struct device*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 

__attribute__((used)) static int a6xx_gmu_rpmh_arc_votes_init(struct device *dev, u32 *votes,
		unsigned long *freqs, int freqs_count,
		u16 *pri, int pri_count,
		u16 *sec, int sec_count)
{
	int i, j;

	/* Construct a vote for each frequency */
	for (i = 0; i < freqs_count; i++) {
		u8 pindex = 0, sindex = 0;
		u32 level = a6xx_gmu_get_arc_level(dev, freqs[i]);

		/* Get the primary index that matches the arc level */
		for (j = 0; j < pri_count; j++) {
			if (pri[j] >= level) {
				pindex = j;
				break;
			}
		}

		if (j == pri_count) {
			dev_err(dev,
				"Level %u not found in in the RPMh list\n",
					level);
			dev_err(dev, "Available levels:\n");
			for (j = 0; j < pri_count; j++)
				dev_err(dev, "  %u\n", pri[j]);

			return -EINVAL;
		}

		/*
		 * Look for a level in in the secondary list that matches. If
		 * nothing fits, use the maximum non zero vote
		 */

		for (j = 0; j < sec_count; j++) {
			if (sec[j] >= level) {
				sindex = j;
				break;
			} else if (sec[j]) {
				sindex = j;
			}
		}

		/* Construct the vote */
		votes[i] = ((pri[pindex] & 0xffff) << 16) |
			(sindex << 8) | pindex;
	}

	return 0;
}