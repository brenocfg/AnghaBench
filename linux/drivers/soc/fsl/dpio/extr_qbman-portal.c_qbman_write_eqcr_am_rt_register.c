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
struct qbman_swp {int dummy; } ;

/* Variables and functions */
 scalar_t__ QBMAN_CINH_SWP_EQCR_AM_RT ; 
 scalar_t__ QBMAN_CINH_SWP_EQCR_AM_RT2 ; 
 int /*<<< orphan*/  QMAN_RT_MODE ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qbman_write_eqcr_am_rt_register(struct qbman_swp *p,
						   u8 idx)
{
	if (idx < 16)
		qbman_write_register(p, QBMAN_CINH_SWP_EQCR_AM_RT + idx * 4,
				     QMAN_RT_MODE);
	else
		qbman_write_register(p, QBMAN_CINH_SWP_EQCR_AM_RT2 +
				     (idx - 16) * 4,
				     QMAN_RT_MODE);
}