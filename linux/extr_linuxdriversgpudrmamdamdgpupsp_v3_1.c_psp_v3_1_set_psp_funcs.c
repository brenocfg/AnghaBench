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
struct psp_context {int /*<<< orphan*/ * funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  psp_v3_1_funcs ; 

void psp_v3_1_set_psp_funcs(struct psp_context *psp)
{
	psp->funcs = &psp_v3_1_funcs;
}