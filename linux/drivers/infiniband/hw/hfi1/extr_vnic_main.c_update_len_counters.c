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
struct opa_vnic_grp_stats {int /*<<< orphan*/  s_64; int /*<<< orphan*/  s_65_127; int /*<<< orphan*/  s_128_255; int /*<<< orphan*/  s_256_511; int /*<<< orphan*/  s_512_1023; int /*<<< orphan*/  s_1024_1518; int /*<<< orphan*/  s_1519_max; } ;

/* Variables and functions */

__attribute__((used)) static inline void update_len_counters(struct opa_vnic_grp_stats *grp,
				       int len)
{
	/* account for 4 byte FCS */
	if (len >= 1515)
		grp->s_1519_max++;
	else if (len >= 1020)
		grp->s_1024_1518++;
	else if (len >= 508)
		grp->s_512_1023++;
	else if (len >= 252)
		grp->s_256_511++;
	else if (len >= 124)
		grp->s_128_255++;
	else if (len >= 61)
		grp->s_65_127++;
	else
		grp->s_64++;
}