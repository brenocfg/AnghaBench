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

/* Variables and functions */
 int /*<<< orphan*/ * color_table ; 
 int /*<<< orphan*/ * default_blu ; 
 int /*<<< orphan*/ * default_grn ; 
 int /*<<< orphan*/ * default_red ; 
 int /*<<< orphan*/  newport_bfwait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newport_cmap_setaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newport_cmap_setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npregs ; 

__attribute__((used)) static inline void newport_init_cmap(void)
{
	unsigned short i;

	for (i = 0; i < 16; i++) {
		newport_bfwait(npregs);
		newport_cmap_setaddr(npregs, color_table[i]);
		newport_cmap_setrgb(npregs,
				    default_red[i],
				    default_grn[i], default_blu[i]);
	}
}