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
struct nvkm_outp {int dummy; } ;
struct nvkm_dp {int /*<<< orphan*/  hpd; } ;

/* Variables and functions */
 struct nvkm_dp* nvkm_dp (struct nvkm_outp*) ; 
 int /*<<< orphan*/  nvkm_dp_enable (struct nvkm_dp*,int) ; 
 int /*<<< orphan*/  nvkm_notify_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvkm_dp_fini(struct nvkm_outp *outp)
{
	struct nvkm_dp *dp = nvkm_dp(outp);
	nvkm_notify_put(&dp->hpd);
	nvkm_dp_enable(dp, false);
}