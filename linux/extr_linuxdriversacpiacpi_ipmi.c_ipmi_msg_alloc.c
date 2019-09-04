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
struct acpi_ipmi_msg {int /*<<< orphan*/  msg_done; struct acpi_ipmi_device* device; int /*<<< orphan*/  head; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  kref; } ;
struct acpi_ipmi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IPMI_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct acpi_ipmi_device* acpi_ipmi_dev_get () ; 
 int /*<<< orphan*/  acpi_ipmi_dev_put (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct acpi_ipmi_msg* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_ipmi_msg *ipmi_msg_alloc(void)
{
	struct acpi_ipmi_device *ipmi;
	struct acpi_ipmi_msg *ipmi_msg;

	ipmi = acpi_ipmi_dev_get();
	if (!ipmi)
		return NULL;

	ipmi_msg = kzalloc(sizeof(struct acpi_ipmi_msg), GFP_KERNEL);
	if (!ipmi_msg) {
		acpi_ipmi_dev_put(ipmi);
		return NULL;
	}

	kref_init(&ipmi_msg->kref);
	init_completion(&ipmi_msg->tx_complete);
	INIT_LIST_HEAD(&ipmi_msg->head);
	ipmi_msg->device = ipmi;
	ipmi_msg->msg_done = ACPI_IPMI_UNKNOWN;

	return ipmi_msg;
}