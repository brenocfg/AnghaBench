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
struct qman_portal {int dummy; } ;

/* Variables and functions */
 int __poll_portal_fast (struct qman_portal*,unsigned int) ; 

int qman_p_poll_dqrr(struct qman_portal *p, unsigned int limit)
{
	return __poll_portal_fast(p, limit);
}