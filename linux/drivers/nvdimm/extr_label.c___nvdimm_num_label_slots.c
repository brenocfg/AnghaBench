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
struct TYPE_2__ {size_t config_size; } ;
struct nvdimm_drvdata {TYPE_1__ nsarea; } ;

/* Variables and functions */
 size_t sizeof_namespace_label (struct nvdimm_drvdata*) ; 

__attribute__((used)) static int __nvdimm_num_label_slots(struct nvdimm_drvdata *ndd,
		size_t index_size)
{
	return (ndd->nsarea.config_size - index_size * 2) /
			sizeof_namespace_label(ndd);
}