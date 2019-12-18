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
typedef  int /*<<< orphan*/  tmpbuf ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ctlr_info {int raid_offload_debug; TYPE_1__* pdev; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct ctlr_info* shost_to_hba (struct Scsi_Host*) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static ssize_t host_store_raid_offload_debug(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	int debug_level, len;
	struct ctlr_info *h;
	struct Scsi_Host *shost = class_to_shost(dev);
	char tmpbuf[10];

	if (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		return -EACCES;
	len = count > sizeof(tmpbuf) - 1 ? sizeof(tmpbuf) - 1 : count;
	strncpy(tmpbuf, buf, len);
	tmpbuf[len] = '\0';
	if (sscanf(tmpbuf, "%d", &debug_level) != 1)
		return -EINVAL;
	if (debug_level < 0)
		debug_level = 0;
	h = shost_to_hba(shost);
	h->raid_offload_debug = debug_level;
	dev_warn(&h->pdev->dev, "hpsa: Set raid_offload_debug level = %d\n",
		h->raid_offload_debug);
	return count;
}