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
typedef  size_t u8 ;
struct nvkm_pm {int dummy; } ;
struct nvkm_perfsig {int /*<<< orphan*/  name; } ;
struct nvkm_perfdom {struct nvkm_perfsig* signal; } ;

/* Variables and functions */
 struct nvkm_perfdom* nvkm_perfdom_find (struct nvkm_pm*,size_t) ; 

__attribute__((used)) static struct nvkm_perfsig *
nvkm_perfsig_find(struct nvkm_pm *pm, u8 di, u8 si, struct nvkm_perfdom **pdom)
{
	struct nvkm_perfdom *dom = *pdom;

	if (dom == NULL) {
		dom = nvkm_perfdom_find(pm, di);
		if (dom == NULL)
			return NULL;
		*pdom = dom;
	}

	if (!dom->signal[si].name)
		return NULL;
	return &dom->signal[si];
}