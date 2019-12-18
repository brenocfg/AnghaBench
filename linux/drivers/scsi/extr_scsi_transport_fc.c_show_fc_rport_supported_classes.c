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
struct fc_rport {scalar_t__ supported_classes; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ FC_COS_UNSPECIFIED ; 
 int /*<<< orphan*/  get_fc_cos_names (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 struct fc_rport* transport_class_to_rport (struct device*) ; 

__attribute__((used)) static ssize_t
show_fc_rport_supported_classes (struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct fc_rport *rport = transport_class_to_rport(dev);
	if (rport->supported_classes == FC_COS_UNSPECIFIED)
		return snprintf(buf, 20, "unspecified\n");
	return get_fc_cos_names(rport->supported_classes, buf);
}