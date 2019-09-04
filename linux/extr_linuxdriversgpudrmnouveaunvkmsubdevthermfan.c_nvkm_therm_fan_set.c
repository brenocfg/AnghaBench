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
struct nvkm_therm {int /*<<< orphan*/  fan; } ;

/* Variables and functions */
 int nvkm_fan_update (int /*<<< orphan*/ ,int,int) ; 

int
nvkm_therm_fan_set(struct nvkm_therm *therm, bool immediate, int percent)
{
	return nvkm_fan_update(therm->fan, immediate, percent);
}