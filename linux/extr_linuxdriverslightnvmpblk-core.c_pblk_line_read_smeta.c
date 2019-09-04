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
typedef  int /*<<< orphan*/  u64 ;
struct pblk_line {int dummy; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_READ_RECOV ; 
 int /*<<< orphan*/  pblk_line_smeta_start (struct pblk*,struct pblk_line*) ; 
 int pblk_line_submit_smeta_io (struct pblk*,struct pblk_line*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pblk_line_read_smeta(struct pblk *pblk, struct pblk_line *line)
{
	u64 bpaddr = pblk_line_smeta_start(pblk, line);

	return pblk_line_submit_smeta_io(pblk, line, bpaddr, PBLK_READ_RECOV);
}