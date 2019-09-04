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
struct mthca_eq {int eqn; int nent; } ;
struct mthca_dev {int /*<<< orphan*/  doorbell_lock; scalar_t__ kar; } ;

/* Variables and functions */
 int MTHCA_EQ_DB_SET_CI ; 
 scalar_t__ MTHCA_EQ_DOORBELL ; 
 int /*<<< orphan*/  MTHCA_GET_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_write64 (int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void tavor_set_eq_ci(struct mthca_dev *dev, struct mthca_eq *eq, u32 ci)
{
	/*
	 * This barrier makes sure that all updates to ownership bits
	 * done by set_eqe_hw() hit memory before the consumer index
	 * is updated.  set_eq_ci() allows the HCA to possibly write
	 * more EQ entries, and we want to avoid the exceedingly
	 * unlikely possibility of the HCA writing an entry and then
	 * having set_eqe_hw() overwrite the owner field.
	 */
	wmb();
	mthca_write64(MTHCA_EQ_DB_SET_CI | eq->eqn, ci & (eq->nent - 1),
		      dev->kar + MTHCA_EQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&dev->doorbell_lock));
}