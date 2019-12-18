#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpu_kms {struct dpu_hw_vbif** hw_vbif; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_mem_type ) (struct dpu_hw_vbif*,int,int /*<<< orphan*/ ) ;} ;
struct dpu_hw_vbif {TYPE_2__* cap; TYPE_1__ ops; } ;
struct TYPE_4__ {int memtype_count; int /*<<< orphan*/ * memtype; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_hw_vbif**) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_vbif*,int,int /*<<< orphan*/ ) ; 

void dpu_vbif_init_memtypes(struct dpu_kms *dpu_kms)
{
	struct dpu_hw_vbif *vbif;
	int i, j;

	for (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbif); i++) {
		vbif = dpu_kms->hw_vbif[i];
		if (vbif && vbif->cap && vbif->ops.set_mem_type) {
			for (j = 0; j < vbif->cap->memtype_count; j++)
				vbif->ops.set_mem_type(
						vbif, j, vbif->cap->memtype[j]);
		}
	}
}