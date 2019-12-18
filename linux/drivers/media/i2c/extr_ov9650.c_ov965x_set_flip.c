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
struct TYPE_6__ {TYPE_2__* vflip; TYPE_1__* hflip; } ;
struct ov965x {TYPE_3__ ctrls; } ;
struct TYPE_5__ {scalar_t__ val; } ;
struct TYPE_4__ {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVFP_FLIP ; 
 int /*<<< orphan*/  MVFP_MIRROR ; 
 int /*<<< orphan*/  REG_MVFP ; 
 int ov965x_write (struct ov965x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov965x_set_flip(struct ov965x *ov965x)
{
	u8 mvfp = 0;

	if (ov965x->ctrls.hflip->val)
		mvfp |= MVFP_MIRROR;

	if (ov965x->ctrls.vflip->val)
		mvfp |= MVFP_FLIP;

	return ov965x_write(ov965x, REG_MVFP, mvfp);
}