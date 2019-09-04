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
struct pblk_line {int /*<<< orphan*/  emeta_ssec; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_READ ; 
 int pblk_line_submit_emeta_io (struct pblk*,struct pblk_line*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pblk_line_read_emeta(struct pblk *pblk, struct pblk_line *line,
			 void *emeta_buf)
{
	return pblk_line_submit_emeta_io(pblk, line, emeta_buf,
						line->emeta_ssec, PBLK_READ);
}