#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  memory; } ;
struct gt215_ram {TYPE_1__ ltrain; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gt215_link_train_fini(struct gt215_ram *ram)
{
	nvkm_memory_unref(&ram->ltrain.memory);
}