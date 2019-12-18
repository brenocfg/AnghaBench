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
struct srb {int /*<<< orphan*/  ref_count; } ;
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sp_get(struct srb *sp)
{
	if (!refcount_inc_not_zero((refcount_t *)&sp->ref_count))
		/* kref get fail */
		return ENXIO;
	else
		return 0;
}