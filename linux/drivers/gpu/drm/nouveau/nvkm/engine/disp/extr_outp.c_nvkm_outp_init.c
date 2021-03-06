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
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_outp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_outp_init_route (struct nvkm_outp*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_outp*) ; 

void
nvkm_outp_init(struct nvkm_outp *outp)
{
	nvkm_outp_init_route(outp);
	if (outp->func->init)
		outp->func->init(outp);
}