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
struct ramfuc {int /*<<< orphan*/ * fb; int /*<<< orphan*/  memx; } ;

/* Variables and functions */
 int nvkm_memx_fini (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
ramfuc_exec(struct ramfuc *ram, bool exec)
{
	int ret = 0;
	if (ram->fb) {
		ret = nvkm_memx_fini(&ram->memx, exec);
		ram->fb = NULL;
	}
	return ret;
}