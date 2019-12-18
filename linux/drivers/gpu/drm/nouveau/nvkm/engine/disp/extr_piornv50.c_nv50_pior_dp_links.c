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
struct TYPE_2__ {int /*<<< orphan*/  ef; int /*<<< orphan*/  bw; int /*<<< orphan*/  nr; } ;
struct nvkm_ior {TYPE_1__ dp; } ;
struct nvkm_i2c_aux {int dummy; } ;

/* Variables and functions */
 int nvkm_i2c_aux_lnk_ctl (struct nvkm_i2c_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_pior_dp_links(struct nvkm_ior *pior, struct nvkm_i2c_aux *aux)
{
	int ret = nvkm_i2c_aux_lnk_ctl(aux, pior->dp.nr, pior->dp.bw,
					    pior->dp.ef);
	if (ret)
		return ret;
	return 1;
}