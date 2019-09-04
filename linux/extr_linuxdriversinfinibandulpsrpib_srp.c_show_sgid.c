#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct srp_target_port {TYPE_1__ sgid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct srp_target_port* host_to_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_sgid(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct srp_target_port *target = host_to_target(class_to_shost(dev));

	return sprintf(buf, "%pI6\n", target->sgid.raw);
}