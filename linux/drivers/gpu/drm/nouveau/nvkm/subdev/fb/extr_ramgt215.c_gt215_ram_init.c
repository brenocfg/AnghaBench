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
struct gt215_ram {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gt215_link_train_init (struct gt215_ram*) ; 
 struct gt215_ram* gt215_ram (struct nvkm_ram*) ; 

__attribute__((used)) static int
gt215_ram_init(struct nvkm_ram *base)
{
	struct gt215_ram *ram = gt215_ram(base);
	gt215_link_train_init(ram);
	return 0;
}