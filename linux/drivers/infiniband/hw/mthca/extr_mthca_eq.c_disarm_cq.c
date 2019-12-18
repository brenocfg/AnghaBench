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
struct mthca_dev {int /*<<< orphan*/  doorbell_lock; scalar_t__ kar; } ;

/* Variables and functions */
 int MTHCA_EQ_DB_DISARM_CQ ; 
 scalar_t__ MTHCA_EQ_DOORBELL ; 
 int /*<<< orphan*/  MTHCA_GET_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_write64 (int,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void disarm_cq(struct mthca_dev *dev, int eqn, int cqn)
{
	if (!mthca_is_memfree(dev)) {
		mthca_write64(MTHCA_EQ_DB_DISARM_CQ | eqn, cqn,
			      dev->kar + MTHCA_EQ_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->doorbell_lock));
	}
}