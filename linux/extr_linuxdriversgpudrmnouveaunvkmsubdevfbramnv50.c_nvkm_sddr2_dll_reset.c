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
struct nv50_ramseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mr ; 
 int /*<<< orphan*/  ram_mask (struct nv50_ramseq*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ram_nsec (struct nv50_ramseq*,int) ; 

__attribute__((used)) static void
nvkm_sddr2_dll_reset(struct nv50_ramseq *hwsq)
{
	ram_mask(hwsq, mr[0], 0x100, 0x100);
	ram_mask(hwsq, mr[0], 0x100, 0x000);
	ram_nsec(hwsq, 24000);
}