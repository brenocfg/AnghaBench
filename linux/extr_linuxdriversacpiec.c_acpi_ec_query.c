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
typedef  scalar_t__ u8 ;
struct acpi_ec_query {int /*<<< orphan*/  work; int /*<<< orphan*/  handler; int /*<<< orphan*/  transaction; } ;
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODATA ; 
 int ENOMEM ; 
 struct acpi_ec_query* acpi_ec_create_query (scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ec_delete_query (struct acpi_ec_query*) ; 
 int /*<<< orphan*/  acpi_ec_get_query_handler_by_value (struct acpi_ec*,scalar_t__) ; 
 int acpi_ec_transaction (struct acpi_ec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_dbg_evt (char*,scalar_t__) ; 
 int /*<<< orphan*/  ec_query_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_ec_query(struct acpi_ec *ec, u8 *data)
{
	u8 value = 0;
	int result;
	struct acpi_ec_query *q;

	q = acpi_ec_create_query(&value);
	if (!q)
		return -ENOMEM;

	/*
	 * Query the EC to find out which _Qxx method we need to evaluate.
	 * Note that successful completion of the query causes the ACPI_EC_SCI
	 * bit to be cleared (and thus clearing the interrupt source).
	 */
	result = acpi_ec_transaction(ec, &q->transaction);
	if (!value)
		result = -ENODATA;
	if (result)
		goto err_exit;

	q->handler = acpi_ec_get_query_handler_by_value(ec, value);
	if (!q->handler) {
		result = -ENODATA;
		goto err_exit;
	}

	/*
	 * It is reported that _Qxx are evaluated in a parallel way on
	 * Windows:
	 * https://bugzilla.kernel.org/show_bug.cgi?id=94411
	 *
	 * Put this log entry before schedule_work() in order to make
	 * it appearing before any other log entries occurred during the
	 * work queue execution.
	 */
	ec_dbg_evt("Query(0x%02x) scheduled", value);
	if (!queue_work(ec_query_wq, &q->work)) {
		ec_dbg_evt("Query(0x%02x) overlapped", value);
		result = -EBUSY;
	}

err_exit:
	if (result)
		acpi_ec_delete_query(q);
	if (data)
		*data = value;
	return result;
}