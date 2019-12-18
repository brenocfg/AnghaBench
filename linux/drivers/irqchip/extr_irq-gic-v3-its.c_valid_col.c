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
struct its_collection {int target_address; } ;

/* Variables and functions */
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static struct its_collection *valid_col(struct its_collection *col)
{
	if (WARN_ON_ONCE(col->target_address & GENMASK_ULL(15, 0)))
		return NULL;

	return col;
}