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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_freq; } ;
struct nvbios_pll {TYPE_1__ vco2; } ;

/* Variables and functions */
 int getMNP_double (struct nvkm_subdev*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 int getMNP_single (struct nvkm_subdev*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 

int
nv04_pll_calc(struct nvkm_subdev *subdev, struct nvbios_pll *info, u32 freq,
	      int *N1, int *M1, int *N2, int *M2, int *P)
{
	int ret;

	if (!info->vco2.max_freq || !N2) {
		ret = getMNP_single(subdev, info, freq, N1, M1, P);
		if (N2) {
			*N2 = 1;
			*M2 = 1;
		}
	} else {
		ret = getMNP_double(subdev, info, freq, N1, M1, N2, M2, P);
	}

	if (!ret)
		nvkm_error(subdev, "unable to compute acceptable pll values\n");
	return ret;
}