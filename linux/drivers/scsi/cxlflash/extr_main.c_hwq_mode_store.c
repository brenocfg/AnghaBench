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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxlflash_cfg {struct afu* afu; TYPE_1__* dev; } ;
struct afu {int hwq_mode; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int MAX_HWQ_MODE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/ * hwq_mode_name ; 
 struct cxlflash_cfg* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t hwq_mode_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct cxlflash_cfg *cfg = shost_priv(shost);
	struct device *cfgdev = &cfg->dev->dev;
	struct afu *afu = cfg->afu;
	int i;
	u32 mode = MAX_HWQ_MODE;

	for (i = 0; i < MAX_HWQ_MODE; i++) {
		if (!strncmp(hwq_mode_name[i], buf, strlen(hwq_mode_name[i]))) {
			mode = i;
			break;
		}
	}

	if (mode >= MAX_HWQ_MODE) {
		dev_info(cfgdev, "Invalid HWQ steering mode.\n");
		return -EINVAL;
	}

	afu->hwq_mode = mode;

	return count;
}