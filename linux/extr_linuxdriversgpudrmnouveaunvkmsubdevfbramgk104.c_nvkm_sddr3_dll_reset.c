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
struct gk104_ramfuc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mr ; 
 int /*<<< orphan*/  ram_mask (struct gk104_ramfuc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ram_nuke (struct gk104_ramfuc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvkm_sddr3_dll_reset(struct gk104_ramfuc *fuc)
{
	ram_nuke(fuc, mr[0]);
	ram_mask(fuc, mr[0], 0x100, 0x100);
	ram_mask(fuc, mr[0], 0x100, 0x000);
}