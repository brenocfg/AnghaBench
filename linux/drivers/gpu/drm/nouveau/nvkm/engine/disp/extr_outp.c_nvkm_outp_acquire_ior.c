#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct TYPE_6__ {TYPE_2__ sorconf; } ;
struct nvkm_outp {int /*<<< orphan*/  acquired; TYPE_3__ info; struct nvkm_ior* ior; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; struct nvkm_outp* outp; } ;
struct nvkm_ior {TYPE_1__ asy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
nvkm_outp_acquire_ior(struct nvkm_outp *outp, u8 user, struct nvkm_ior *ior)
{
	outp->ior = ior;
	outp->ior->asy.outp = outp;
	outp->ior->asy.link = outp->info.sorconf.link;
	outp->acquired |= user;
	return 0;
}