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

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kgdb_connected ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kgdbts_post_exp_handler(void)
{
	/* decrement the module count when the debugger detaches */
	if (!kgdb_connected)
		module_put(THIS_MODULE);
}