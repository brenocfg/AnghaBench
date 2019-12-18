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
struct tpg_data {int /*<<< orphan*/ ** random_line; int /*<<< orphan*/ ** black_line; int /*<<< orphan*/ ** contrast_line; int /*<<< orphan*/ *** downsampled_lines; int /*<<< orphan*/ *** lines; } ;

/* Variables and functions */
 unsigned int TPG_MAX_PAT_LINES ; 
 unsigned int TPG_MAX_PLANES ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void tpg_free(struct tpg_data *tpg)
{
	unsigned pat;
	unsigned plane;

	for (pat = 0; pat < TPG_MAX_PAT_LINES; pat++)
		for (plane = 0; plane < TPG_MAX_PLANES; plane++) {
			vfree(tpg->lines[pat][plane]);
			tpg->lines[pat][plane] = NULL;
			if (plane == 0)
				continue;
			vfree(tpg->downsampled_lines[pat][plane]);
			tpg->downsampled_lines[pat][plane] = NULL;
		}
	for (plane = 0; plane < TPG_MAX_PLANES; plane++) {
		vfree(tpg->contrast_line[plane]);
		vfree(tpg->black_line[plane]);
		vfree(tpg->random_line[plane]);
		tpg->contrast_line[plane] = NULL;
		tpg->black_line[plane] = NULL;
		tpg->random_line[plane] = NULL;
	}
}