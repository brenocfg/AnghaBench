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
struct nvkm_ram {int dummy; } ;
struct nv50_ram {int /*<<< orphan*/  hwsq; } ;

/* Variables and functions */
 struct nv50_ram* nv50_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  ram_exec (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nv50_ram_tidy(struct nvkm_ram *base)
{
	struct nv50_ram *ram = nv50_ram(base);
	ram_exec(&ram->hwsq, false);
}