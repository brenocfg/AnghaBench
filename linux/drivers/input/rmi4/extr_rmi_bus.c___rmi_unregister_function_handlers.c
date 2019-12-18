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
 int /*<<< orphan*/ * fn_handlers ; 
 int /*<<< orphan*/  rmi_unregister_function_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rmi_unregister_function_handlers(int start_idx)
{
	int i;

	for (i = start_idx; i >= 0; i--)
		rmi_unregister_function_handler(fn_handlers[i]);
}