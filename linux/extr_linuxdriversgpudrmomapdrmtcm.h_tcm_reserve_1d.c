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
typedef  int u32 ;
struct tcm_area {int is2d; struct tcm* tcm; } ;
struct tcm {int width; scalar_t__ (* reserve_1d ) (struct tcm*,int,struct tcm_area*) ;scalar_t__ height; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ stub1 (struct tcm*,int,struct tcm_area*) ; 

__attribute__((used)) static inline s32 tcm_reserve_1d(struct tcm *tcm, u32 slots,
				 struct tcm_area *area)
{
	/* perform rudimentary error checking */
	s32 res = tcm  == NULL ? -ENODEV :
		(area == NULL || slots == 0) ? -EINVAL :
		slots > (tcm->width * (u32) tcm->height) ? -ENOMEM : 0;

	if (!res) {
		area->is2d = false;
		res = tcm->reserve_1d(tcm, slots, area);
		area->tcm = res ? NULL : tcm;
	}

	return res;
}