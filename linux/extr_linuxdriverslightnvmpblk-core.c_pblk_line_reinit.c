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
struct pblk_line {int /*<<< orphan*/ * emeta; int /*<<< orphan*/ * smeta; int /*<<< orphan*/ * invalid_bitmap; int /*<<< orphan*/ * map_bitmap; int /*<<< orphan*/ * vsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_ENTRY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_line_reinit(struct pblk_line *line)
{
	*line->vsc = cpu_to_le32(EMPTY_ENTRY);

	line->map_bitmap = NULL;
	line->invalid_bitmap = NULL;
	line->smeta = NULL;
	line->emeta = NULL;
}