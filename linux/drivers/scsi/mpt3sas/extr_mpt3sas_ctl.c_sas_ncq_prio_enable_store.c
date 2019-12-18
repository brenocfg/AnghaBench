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
struct scsi_device {struct MPT3SAS_DEVICE* hostdata; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct MPT3SAS_DEVICE {int ncq_prio_enable; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 int /*<<< orphan*/  scsih_ncq_prio_supp (struct scsi_device*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sas_ncq_prio_enable_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct MPT3SAS_DEVICE *sas_device_priv_data = sdev->hostdata;
	bool ncq_prio_enable = 0;

	if (kstrtobool(buf, &ncq_prio_enable))
		return -EINVAL;

	if (!scsih_ncq_prio_supp(sdev))
		return -EINVAL;

	sas_device_priv_data->ncq_prio_enable = ncq_prio_enable;
	return strlen(buf);
}