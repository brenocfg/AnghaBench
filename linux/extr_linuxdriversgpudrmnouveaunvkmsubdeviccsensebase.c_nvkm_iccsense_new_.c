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
struct nvkm_iccsense {int /*<<< orphan*/  rails; int /*<<< orphan*/  sensors; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nvkm_iccsense* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_iccsense_ctor (struct nvkm_device*,int,struct nvkm_iccsense*) ; 

int
nvkm_iccsense_new_(struct nvkm_device *device, int index,
		   struct nvkm_iccsense **iccsense)
{
	if (!(*iccsense = kzalloc(sizeof(**iccsense), GFP_KERNEL)))
		return -ENOMEM;
	INIT_LIST_HEAD(&(*iccsense)->sensors);
	INIT_LIST_HEAD(&(*iccsense)->rails);
	nvkm_iccsense_ctor(device, index, *iccsense);
	return 0;
}