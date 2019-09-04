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
typedef  scalar_t__ u16 ;
struct tcm_area {int is2d; struct tcm* tcm; } ;
struct tcm {scalar_t__ height; scalar_t__ width; scalar_t__ (* reserve_2d ) (struct tcm*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct tcm_area*) ;} ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ stub1 (struct tcm*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct tcm_area*) ; 

__attribute__((used)) static inline s32 tcm_reserve_2d(struct tcm *tcm, u16 width, u16 height,
				u16 align, s16 offset, u16 slot_bytes,
				struct tcm_area *area)
{
	/* perform rudimentary error checking */
	s32 res = tcm  == NULL ? -ENODEV :
		(area == NULL || width == 0 || height == 0 ||
		 /* align must be a 2 power */
		 (align & (align - 1))) ? -EINVAL :
		(height > tcm->height || width > tcm->width) ? -ENOMEM : 0;

	if (!res) {
		area->is2d = true;
		res = tcm->reserve_2d(tcm, height, width, align, offset,
					slot_bytes, area);
		area->tcm = res ? NULL : tcm;
	}

	return res;
}