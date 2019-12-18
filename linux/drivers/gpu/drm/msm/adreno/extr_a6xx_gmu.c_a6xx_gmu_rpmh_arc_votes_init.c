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
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (unsigned int const*) ; 
 int PTR_ERR (unsigned int const*) ; 
 unsigned int a6xx_gmu_get_arc_level (struct device*,unsigned long) ; 
 unsigned int* cmd_db_read_aux_data (char const*,size_t*) ; 

__attribute__((used)) static int a6xx_gmu_rpmh_arc_votes_init(struct device *dev, u32 *votes,
		unsigned long *freqs, int freqs_count, const char *id)
{
	int i, j;
	const u16 *pri, *sec;
	size_t pri_count, sec_count;

	pri = cmd_db_read_aux_data(id, &pri_count);
	if (IS_ERR(pri))
		return PTR_ERR(pri);
	/*
	 * The data comes back as an array of unsigned shorts so adjust the
	 * count accordingly
	 */
	pri_count >>= 1;
	if (!pri_count)
		return -EINVAL;

	sec = cmd_db_read_aux_data("mx.lvl", &sec_count);
	if (IS_ERR(sec))
		return PTR_ERR(sec);

	sec_count >>= 1;
	if (!sec_count)
		return -EINVAL;

	/* Construct a vote for each frequency */
	for (i = 0; i < freqs_count; i++) {
		u8 pindex = 0, sindex = 0;
		unsigned int level = a6xx_gmu_get_arc_level(dev, freqs[i]);

		/* Get the primary index that matches the arc level */
		for (j = 0; j < pri_count; j++) {
			if (pri[j] >= level) {
				pindex = j;
				break;
			}
		}

		if (j == pri_count) {
			DRM_DEV_ERROR(dev,
				"Level %u not found in in the RPMh list\n",
					level);
			DRM_DEV_ERROR(dev, "Available levels:\n");
			for (j = 0; j < pri_count; j++)
				DRM_DEV_ERROR(dev, "  %u\n", pri[j]);

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