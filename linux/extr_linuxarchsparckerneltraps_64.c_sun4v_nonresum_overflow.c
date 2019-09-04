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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4v_nonresum_oflow_cnt ; 

void sun4v_nonresum_overflow(struct pt_regs *regs)
{
	/* XXX Actually even this can make not that much sense.  Perhaps
	 * XXX we should just pull the plug and panic directly from here?
	 */
	atomic_inc(&sun4v_nonresum_oflow_cnt);
}