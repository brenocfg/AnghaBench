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
struct nvkm_fault {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gp100_fault ; 
 int nvkm_fault_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_fault**) ; 

int
gp100_fault_new(struct nvkm_device *device, int index,
		struct nvkm_fault **pfault)
{
	return nvkm_fault_new_(&gp100_fault, device, index, pfault);
}