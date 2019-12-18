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

/* Variables and functions */
 int /*<<< orphan*/  nvkm_falcon_disable (struct nvkm_falcon*) ; 
 int nvkm_falcon_enable (struct nvkm_falcon*) ; 

int
nvkm_falcon_reset(struct nvkm_falcon *falcon)
{
	nvkm_falcon_disable(falcon);
	return nvkm_falcon_enable(falcon);
}