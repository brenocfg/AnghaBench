#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_outp {struct nvkm_ior* ior; TYPE_1__* func; int /*<<< orphan*/  acquired; } ;
struct TYPE_4__ {int /*<<< orphan*/ * outp; } ;
struct nvkm_ior {TYPE_2__ asy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct nvkm_outp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OUTP_TRACE (struct nvkm_outp*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_ior*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_outp*) ; 

void
nvkm_outp_release(struct nvkm_outp *outp, u8 user)
{
	struct nvkm_ior *ior = outp->ior;
	OUTP_TRACE(outp, "release %02x &= %02x %p", outp->acquired, ~user, ior);
	if (ior) {
		outp->acquired &= ~user;
		if (!outp->acquired) {
			if (outp->func->release && outp->ior)
				outp->func->release(outp);
			outp->ior->asy.outp = NULL;
			outp->ior = NULL;
		}
	}
}