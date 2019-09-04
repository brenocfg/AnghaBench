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
struct pblk_line {int /*<<< orphan*/ * emeta; int /*<<< orphan*/ * smeta; int /*<<< orphan*/ * map_bitmap; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void pblk_line_recov_close(struct pblk *pblk, struct pblk_line *line)
{
	kfree(line->map_bitmap);
	line->map_bitmap = NULL;
	line->smeta = NULL;
	line->emeta = NULL;
}