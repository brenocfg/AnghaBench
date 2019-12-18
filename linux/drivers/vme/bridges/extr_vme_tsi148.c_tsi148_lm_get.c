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
typedef  int u32 ;
struct vme_lm_resource {int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct tsi148_driver {scalar_t__ base; } ;
struct TYPE_2__ {struct tsi148_driver* driver_priv; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_LMAT ; 
 int TSI148_LCSR_LMAT_AS_A16 ; 
 int TSI148_LCSR_LMAT_AS_A24 ; 
 int TSI148_LCSR_LMAT_AS_A32 ; 
 int TSI148_LCSR_LMAT_AS_A64 ; 
 int TSI148_LCSR_LMAT_AS_M ; 
 int TSI148_LCSR_LMAT_DATA ; 
 int TSI148_LCSR_LMAT_EN ; 
 int TSI148_LCSR_LMAT_NPRIV ; 
 int TSI148_LCSR_LMAT_PGM ; 
 int TSI148_LCSR_LMAT_SUPR ; 
 scalar_t__ TSI148_LCSR_LMBAL ; 
 scalar_t__ TSI148_LCSR_LMBAU ; 
 int VME_A16 ; 
 int VME_A24 ; 
 int VME_A32 ; 
 int VME_A64 ; 
 int VME_DATA ; 
 int VME_PROG ; 
 int VME_SUPER ; 
 int VME_USER ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_join (int,int,unsigned long long*) ; 

__attribute__((used)) static int tsi148_lm_get(struct vme_lm_resource *lm,
	unsigned long long *lm_base, u32 *aspace, u32 *cycle)
{
	u32 lm_base_high, lm_base_low, lm_ctl, enabled = 0;
	struct tsi148_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	lm_base_high = ioread32be(bridge->base + TSI148_LCSR_LMBAU);
	lm_base_low = ioread32be(bridge->base + TSI148_LCSR_LMBAL);
	lm_ctl = ioread32be(bridge->base + TSI148_LCSR_LMAT);

	reg_join(lm_base_high, lm_base_low, lm_base);

	if (lm_ctl & TSI148_LCSR_LMAT_EN)
		enabled = 1;

	if ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A16)
		*aspace |= VME_A16;

	if ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A24)
		*aspace |= VME_A24;

	if ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A32)
		*aspace |= VME_A32;

	if ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A64)
		*aspace |= VME_A64;


	if (lm_ctl & TSI148_LCSR_LMAT_SUPR)
		*cycle |= VME_SUPER;
	if (lm_ctl & TSI148_LCSR_LMAT_NPRIV)
		*cycle |= VME_USER;
	if (lm_ctl & TSI148_LCSR_LMAT_PGM)
		*cycle |= VME_PROG;
	if (lm_ctl & TSI148_LCSR_LMAT_DATA)
		*cycle |= VME_DATA;

	mutex_unlock(&lm->mtx);

	return enabled;
}