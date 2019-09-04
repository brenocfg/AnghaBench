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
struct nvkm_outp {TYPE_1__* func; } ;
struct TYPE_2__ {struct nvkm_outp* (* dtor ) (struct nvkm_outp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nvkm_outp*) ; 
 struct nvkm_outp* stub1 (struct nvkm_outp*) ; 

void
nvkm_outp_del(struct nvkm_outp **poutp)
{
	struct nvkm_outp *outp = *poutp;
	if (outp && !WARN_ON(!outp->func)) {
		if (outp->func->dtor)
			*poutp = outp->func->dtor(outp);
		kfree(*poutp);
		*poutp = NULL;
	}
}