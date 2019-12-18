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
struct slgt_info {unsigned int tbuf_current; int tbuf_count; unsigned int tbuf_start; int /*<<< orphan*/ * tbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  desc_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool unsent_tbufs(struct slgt_info *info)
{
	unsigned int i = info->tbuf_current;
	bool rc = false;

	/*
	 * search backwards from last loaded buffer (precedes tbuf_current)
	 * for first unsent buffer (desc_count > 0)
	 */

	do {
		if (i)
			i--;
		else
			i = info->tbuf_count - 1;
		if (!desc_count(info->tbufs[i]))
			break;
		info->tbuf_start = i;
		rc = true;
	} while (i != info->tbuf_current);

	return rc;
}