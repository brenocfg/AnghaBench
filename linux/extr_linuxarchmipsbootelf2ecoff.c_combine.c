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
struct sect {scalar_t__ len; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void combine(struct sect *base, struct sect *new, int pad)
{
	if (!base->len)
		*base = *new;
	else if (new->len) {
		if (base->vaddr + base->len != new->vaddr) {
			if (pad)
				base->len = new->vaddr - base->vaddr;
			else {
				fprintf(stderr,
					"Non-contiguous data can't be converted.\n");
				exit(1);
			}
		}
		base->len += new->len;
	}
}