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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int /*<<< orphan*/  REFCOUNT_INIT (scalar_t__) ; 
 scalar_t__ REFCOUNT_MAX ; 
 int /*<<< orphan*/  overflow_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 

void lkdtm_REFCOUNT_ADD_OVERFLOW(void)
{
	refcount_t over = REFCOUNT_INIT(REFCOUNT_MAX - 1);

	pr_info("attempting good refcount_add() without overflow\n");
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_dec(&over);
	refcount_add(4, &over);

	pr_info("attempting bad refcount_add() overflow\n");
	refcount_add(4, &over);

	overflow_check(&over);
}