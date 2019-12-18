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
typedef  int u16 ;
struct qbman_swp {int sdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QBMAN_CINH_SWP_SDQCR ; 
 int QB_SDQCR_SRC_MASK ; 
 int QB_SDQCR_SRC_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,int /*<<< orphan*/ ,int) ; 

void qbman_swp_push_set(struct qbman_swp *s, u8 channel_idx, int enable)
{
	u16 dqsrc;

	WARN_ON(channel_idx > 15);
	if (enable)
		s->sdq |= 1 << channel_idx;
	else
		s->sdq &= ~(1 << channel_idx);

	/* Read make the complete src map.  If no channels are enabled
	 * the SDQCR must be 0 or else QMan will assert errors
	 */
	dqsrc = (s->sdq >> QB_SDQCR_SRC_SHIFT) & QB_SDQCR_SRC_MASK;
	if (dqsrc != 0)
		qbman_write_register(s, QBMAN_CINH_SWP_SDQCR, s->sdq);
	else
		qbman_write_register(s, QBMAN_CINH_SWP_SDQCR, 0);
}