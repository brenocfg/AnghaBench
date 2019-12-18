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
typedef  scalar_t__ u32 ;
struct hisi_hba {scalar_t__ intr_coal_ticks; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 size_t EINVAL ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  config_intr_coal_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int kstrtou32 (char const*,int,scalar_t__*) ; 
 struct hisi_hba* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static ssize_t intr_coal_ticks_v3_hw_store(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct hisi_hba *hisi_hba = shost_priv(shost);
	u32 intr_coal_ticks;
	int ret;

	ret = kstrtou32(buf, 10, &intr_coal_ticks);
	if (ret) {
		dev_err(dev, "Input data of interrupt coalesce unmatch\n");
		return -EINVAL;
	}

	if (intr_coal_ticks >= BIT(24)) {
		dev_err(dev, "intr_coal_ticks must be less than 2^24!\n");
		return -EINVAL;
	}

	hisi_hba->intr_coal_ticks = intr_coal_ticks;

	config_intr_coal_v3_hw(hisi_hba);

	return count;
}