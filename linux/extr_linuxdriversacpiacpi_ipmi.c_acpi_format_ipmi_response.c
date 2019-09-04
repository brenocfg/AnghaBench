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
struct acpi_ipmi_msg {scalar_t__ msg_done; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  data; } ;
struct acpi_ipmi_buffer {scalar_t__ status; int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 scalar_t__ ACPI_IPMI_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_format_ipmi_response(struct acpi_ipmi_msg *msg,
				      acpi_integer *value)
{
	struct acpi_ipmi_buffer *buffer;

	/*
	 * value is also used as output parameter. It represents the response
	 * IPMI message returned by IPMI command.
	 */
	buffer = (struct acpi_ipmi_buffer *)value;

	/*
	 * If the flag of msg_done is not set, it means that the IPMI command is
	 * not executed correctly.
	 */
	buffer->status = msg->msg_done;
	if (msg->msg_done != ACPI_IPMI_OK)
		return;

	/*
	 * If the IPMI response message is obtained correctly, the status code
	 * will be ACPI_IPMI_OK
	 */
	buffer->length = msg->rx_len;
	memcpy(buffer->data, msg->data, msg->rx_len);
}