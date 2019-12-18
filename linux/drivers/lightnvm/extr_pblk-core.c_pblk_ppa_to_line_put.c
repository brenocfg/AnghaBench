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
struct ppa_addr {int dummy; } ;
struct pblk_line {int /*<<< orphan*/  ref; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_put_wq ; 
 struct pblk_line* pblk_ppa_to_line (struct pblk*,struct ppa_addr) ; 

void pblk_ppa_to_line_put(struct pblk *pblk, struct ppa_addr ppa)
{
	struct pblk_line *line;

	line = pblk_ppa_to_line(pblk, ppa);
	kref_put(&line->ref, pblk_line_put_wq);
}