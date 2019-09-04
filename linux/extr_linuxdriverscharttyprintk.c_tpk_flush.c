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
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 char* tpk_buffer ; 
 size_t tpk_curr ; 

__attribute__((used)) static void tpk_flush(void)
{
	if (tpk_curr > 0) {
		tpk_buffer[tpk_curr] = '\0';
		pr_info("[U] %s\n", tpk_buffer);
		tpk_curr = 0;
	}
}