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
struct ecc_point {struct ecc_point* y; struct ecc_point* x; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (struct ecc_point*) ; 

__attribute__((used)) static void ecc_free_point(struct ecc_point *p)
{
	if (!p)
		return;

	kzfree(p->x);
	kzfree(p->y);
	kzfree(p);
}