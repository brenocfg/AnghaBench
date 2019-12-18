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
struct nvkm_volt {TYPE_1__* func; } ;
struct TYPE_2__ {int (* speedo_read ) (struct nvkm_volt*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct nvkm_volt*) ; 

__attribute__((used)) static int
nvkm_volt_speedo_read(struct nvkm_volt *volt)
{
	if (volt->func->speedo_read)
		return volt->func->speedo_read(volt);
	return -EINVAL;
}