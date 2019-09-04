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
struct closure {int /*<<< orphan*/  remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closure_put_after_sub (struct closure*,int /*<<< orphan*/ ) ; 

void closure_sub(struct closure *cl, int v)
{
	closure_put_after_sub(cl, atomic_sub_return(v, &cl->remaining));
}