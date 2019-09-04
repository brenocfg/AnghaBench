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
struct pblk_line {int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  map_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_reinit (struct pblk_line*) ; 

void pblk_line_free(struct pblk_line *line)
{
	kfree(line->map_bitmap);
	kfree(line->invalid_bitmap);

	pblk_line_reinit(line);
}