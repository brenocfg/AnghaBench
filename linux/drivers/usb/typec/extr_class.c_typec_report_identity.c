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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void typec_report_identity(struct device *dev)
{
	sysfs_notify(&dev->kobj, "identity", "id_header");
	sysfs_notify(&dev->kobj, "identity", "cert_stat");
	sysfs_notify(&dev->kobj, "identity", "product");
}