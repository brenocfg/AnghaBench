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
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*) ; 

void
vchiq_loud_error_header(void)
{
	vchiq_log_error(vchiq_core_log_level,
		"============================================================"
		"================");
	vchiq_log_error(vchiq_core_log_level,
		"============================================================"
		"================");
	vchiq_log_error(vchiq_core_log_level, "=====");
}