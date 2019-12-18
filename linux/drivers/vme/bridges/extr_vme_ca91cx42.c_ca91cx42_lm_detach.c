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
struct ca91cx42_driver {scalar_t__ base; int /*<<< orphan*/ ** lm_data; int /*<<< orphan*/ ** lm_callback; } ;
struct TYPE_2__ {struct ca91cx42_driver* driver_priv; } ;

/* Variables and functions */
 int* CA91CX42_LINT_LM ; 
 int CA91CX42_LINT_LM0 ; 
 int CA91CX42_LINT_LM1 ; 
 int CA91CX42_LINT_LM2 ; 
 int CA91CX42_LINT_LM3 ; 
 int CA91CX42_LM_CTL_EN ; 
 scalar_t__ LINT_EN ; 
 scalar_t__ LINT_STAT ; 
 scalar_t__ LM_CTL ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ca91cx42_lm_detach(struct vme_lm_resource *lm, int monitor)
{
	u32 tmp;
	struct ca91cx42_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	/* Disable Location Monitor and ensure previous interrupts are clear */
	tmp = ioread32(bridge->base + LINT_EN);
	tmp &= ~CA91CX42_LINT_LM[monitor];
	iowrite32(tmp, bridge->base + LINT_EN);

	iowrite32(CA91CX42_LINT_LM[monitor],
		 bridge->base + LINT_STAT);

	/* Detach callback */
	bridge->lm_callback[monitor] = NULL;
	bridge->lm_data[monitor] = NULL;

	/* If all location monitors disabled, disable global Location Monitor */
	if ((tmp & (CA91CX42_LINT_LM0 | CA91CX42_LINT_LM1 | CA91CX42_LINT_LM2 |
			CA91CX42_LINT_LM3)) == 0) {
		tmp = ioread32(bridge->base + LM_CTL);
		tmp &= ~CA91CX42_LM_CTL_EN;
		iowrite32(tmp, bridge->base + LM_CTL);
	}

	mutex_unlock(&lm->mtx);

	return 0;
}