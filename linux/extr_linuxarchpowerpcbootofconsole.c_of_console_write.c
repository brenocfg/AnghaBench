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
 int /*<<< orphan*/  of_call_prom (char*,int,int,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  of_stdout_handle ; 

__attribute__((used)) static void of_console_write(const char *buf, int len)
{
	of_call_prom("write", 3, 1, of_stdout_handle, buf, len);
}