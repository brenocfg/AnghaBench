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
struct nvkm_therm {scalar_t__ fan; } ;
struct nvkm_fantog {int percent; } ;

/* Variables and functions */

__attribute__((used)) static int
nvkm_fantog_get(struct nvkm_therm *therm)
{
	struct nvkm_fantog *fan = (void *)therm->fan;
	return fan->percent;
}