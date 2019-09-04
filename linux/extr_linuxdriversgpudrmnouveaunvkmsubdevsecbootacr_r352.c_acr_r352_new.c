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
struct nvkm_acr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_SECBOOT_FALCON_PMU ; 
 int /*<<< orphan*/  acr_r352_func ; 
 struct nvkm_acr* acr_r352_new_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

struct nvkm_acr *
acr_r352_new(unsigned long managed_falcons)
{
	return acr_r352_new_(&acr_r352_func, NVKM_SECBOOT_FALCON_PMU,
			     managed_falcons);
}