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
struct nvkm_subdev {int dummy; } ;

/* Variables and functions */
 void* nvkm_bus (struct nvkm_subdev*) ; 

__attribute__((used)) static void *
nvkm_bus_dtor(struct nvkm_subdev *subdev)
{
	return nvkm_bus(subdev);
}