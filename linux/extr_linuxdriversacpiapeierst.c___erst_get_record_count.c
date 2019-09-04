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
struct apei_exec_context {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERST_GET_RECORD_COUNT ; 
 int apei_exec_ctx_get_output (struct apei_exec_context*) ; 
 int apei_exec_run (struct apei_exec_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erst_exec_ctx_init (struct apei_exec_context*) ; 

__attribute__((used)) static ssize_t __erst_get_record_count(void)
{
	struct apei_exec_context ctx;
	int rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_RECORD_COUNT);
	if (rc)
		return rc;
	return apei_exec_ctx_get_output(&ctx);
}