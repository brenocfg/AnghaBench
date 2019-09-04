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
struct lp_struct {int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_PREEMPT_REQUEST ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp_preempt(void *handle)
{
	struct lp_struct *this_lp = (struct lp_struct *)handle;
	set_bit(LP_PREEMPT_REQUEST, &this_lp->bits);
	return (1);
}