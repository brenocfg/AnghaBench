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
typedef  scalar_t__ u32 ;
struct qman_portal {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QMAN_ITP_MAX ; 
 int /*<<< orphan*/  QM_REG_ITPR ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

int qman_portal_set_iperiod(struct qman_portal *portal, u32 iperiod)
{
	if (!portal || iperiod > QMAN_ITP_MAX)
		return -EINVAL;

	qm_out(&portal->p, QM_REG_ITPR, iperiod);

	return 0;
}