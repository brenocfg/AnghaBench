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
struct nvkm_falcon {int dummy; } ;
struct gf100_gr_fuc {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_falcon_load_dmem (struct nvkm_falcon*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_falcon_load_imem (struct nvkm_falcon*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gf100_gr_init_fw(struct nvkm_falcon *falcon,
		 struct gf100_gr_fuc *code, struct gf100_gr_fuc *data)
{
	nvkm_falcon_load_dmem(falcon, data->data, 0x0, data->size, 0);
	nvkm_falcon_load_imem(falcon, code->data, 0x0, code->size, 0, 0, false);
}