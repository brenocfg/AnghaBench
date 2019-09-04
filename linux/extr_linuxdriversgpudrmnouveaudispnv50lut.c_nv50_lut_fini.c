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
struct nv50_lut {int /*<<< orphan*/ * mem; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_mem_fini (int /*<<< orphan*/ *) ; 

void
nv50_lut_fini(struct nv50_lut *lut)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(lut->mem); i++)
		nvif_mem_fini(&lut->mem[i]);
}