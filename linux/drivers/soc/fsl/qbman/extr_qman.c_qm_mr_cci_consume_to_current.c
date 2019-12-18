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
struct qm_mr {scalar_t__ cmode; int /*<<< orphan*/  ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  QM_REG_MR_CI_CINH ; 
 int /*<<< orphan*/  mr_ptr2idx (int /*<<< orphan*/ ) ; 
 scalar_t__ qm_mr_cci ; 
 int /*<<< orphan*/  qm_out (struct qm_portal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qm_mr_cci_consume_to_current(struct qm_portal *portal)
{
	struct qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->cmode == qm_mr_cci);
	mr->ci = mr_ptr2idx(mr->cursor);
	qm_out(portal, QM_REG_MR_CI_CINH, mr->ci);
}