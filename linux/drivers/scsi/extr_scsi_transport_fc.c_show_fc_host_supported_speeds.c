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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ FC_PORTSPEED_UNKNOWN ; 
 scalar_t__ fc_host_supported_speeds (struct Scsi_Host*) ; 
 int /*<<< orphan*/  get_fc_port_speed_names (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 struct Scsi_Host* transport_class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t
show_fc_host_supported_speeds (struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = transport_class_to_shost(dev);

	if (fc_host_supported_speeds(shost) == FC_PORTSPEED_UNKNOWN)
		return snprintf(buf, 20, "unknown\n");

	return get_fc_port_speed_names(fc_host_supported_speeds(shost), buf);
}