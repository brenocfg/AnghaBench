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
struct sdma_state {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_put (struct sdma_state*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_finalput(struct sdma_state *ss)
{
	sdma_put(ss);
	wait_for_completion(&ss->comp);
}