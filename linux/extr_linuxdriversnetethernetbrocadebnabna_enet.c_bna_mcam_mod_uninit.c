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
struct bna_mcam_mod {int /*<<< orphan*/ * bna; } ;

/* Variables and functions */

__attribute__((used)) static void
bna_mcam_mod_uninit(struct bna_mcam_mod *mcam_mod)
{
	mcam_mod->bna = NULL;
}