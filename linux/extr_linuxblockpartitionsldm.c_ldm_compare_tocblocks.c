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
struct tocblock {scalar_t__ bitmap1_start; scalar_t__ bitmap1_size; scalar_t__ bitmap2_start; scalar_t__ bitmap2_size; int /*<<< orphan*/  bitmap2_name; int /*<<< orphan*/  bitmap1_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool ldm_compare_tocblocks (const struct tocblock *toc1,
				   const struct tocblock *toc2)
{
	BUG_ON (!toc1 || !toc2);

	return ((toc1->bitmap1_start == toc2->bitmap1_start)	&&
		(toc1->bitmap1_size  == toc2->bitmap1_size)	&&
		(toc1->bitmap2_start == toc2->bitmap2_start)	&&
		(toc1->bitmap2_size  == toc2->bitmap2_size)	&&
		!strncmp (toc1->bitmap1_name, toc2->bitmap1_name,
			sizeof (toc1->bitmap1_name))		&&
		!strncmp (toc1->bitmap2_name, toc2->bitmap2_name,
			sizeof (toc1->bitmap2_name)));
}