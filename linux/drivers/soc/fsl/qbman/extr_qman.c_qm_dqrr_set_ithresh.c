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
typedef  scalar_t__ u8 ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QMAN_DQRR_IT_MAX ; 
 int /*<<< orphan*/  QM_REG_DQRR_ITR ; 
 int /*<<< orphan*/  qm_out (struct qm_portal*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int qm_dqrr_set_ithresh(struct qm_portal *portal, u8 ithresh)
{

	if (ithresh > QMAN_DQRR_IT_MAX)
		return -EINVAL;

	qm_out(portal, QM_REG_DQRR_ITR, ithresh);

	return 0;
}