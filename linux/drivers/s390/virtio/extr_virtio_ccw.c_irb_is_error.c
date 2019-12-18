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
struct irb {int /*<<< orphan*/  scsw; } ;

/* Variables and functions */
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_DEV_END ; 
 scalar_t__ scsw_cc (int /*<<< orphan*/ *) ; 
 scalar_t__ scsw_cstat (int /*<<< orphan*/ *) ; 
 int scsw_dstat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int irb_is_error(struct irb *irb)
{
	if (scsw_cstat(&irb->scsw) != 0)
		return 1;
	if (scsw_dstat(&irb->scsw) & ~(DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		return 1;
	if (scsw_cc(&irb->scsw) != 0)
		return 1;
	return 0;
}