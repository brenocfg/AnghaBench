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
struct pblk_line {scalar_t__ left_msecs; } ;

/* Variables and functions */

int pblk_line_is_full(struct pblk_line *line)
{
	return (line->left_msecs == 0);
}