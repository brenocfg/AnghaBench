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
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rmi_unregister_function_handlers (scalar_t__) ; 
 int /*<<< orphan*/  fn_handlers ; 

__attribute__((used)) static void rmi_unregister_function_handlers(void)
{
	__rmi_unregister_function_handlers(ARRAY_SIZE(fn_handlers) - 1);
}