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
typedef  int u8 ;
struct qm_portal {int dummy; } ;

/* Variables and functions */
 int QM_DQRR_SIZE ; 
 int /*<<< orphan*/  QM_REG_CFG ; 
 int qm_in (struct qm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_out (struct qm_portal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void qm_dqrr_set_maxfill(struct qm_portal *portal, u8 mf)
{
	qm_out(portal, QM_REG_CFG, (qm_in(portal, QM_REG_CFG) & 0xff0fffff) |
				   ((mf & (QM_DQRR_SIZE - 1)) << 20));
}