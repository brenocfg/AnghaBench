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
typedef  int /*<<< orphan*/  u32 ;
struct qman_portal {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_REG_ITPR ; 
 int /*<<< orphan*/  qm_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qman_portal_get_iperiod(struct qman_portal *portal, u32 *iperiod)
{
	if (portal && iperiod)
		*iperiod = qm_in(&portal->p, QM_REG_ITPR);
}