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
struct nvif_disp {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

void
nvif_disp_dtor(struct nvif_disp *disp)
{
	nvif_object_fini(&disp->object);
}