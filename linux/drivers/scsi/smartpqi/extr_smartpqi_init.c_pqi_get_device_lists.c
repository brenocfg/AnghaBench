#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct report_lun_header {int dummy; } ;
typedef  struct report_lun_header u8 ;
struct report_phys_lun_extended {int dummy; } ;
struct report_log_lun_extended_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list_length; } ;
struct report_log_lun_extended {TYPE_2__ header; } ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  report_lun_header ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 size_t get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct report_log_lun_extended*) ; 
 struct report_log_lun_extended* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct report_log_lun_extended*,struct report_log_lun_extended*,size_t) ; 
 int /*<<< orphan*/  memset (struct report_lun_header*,int /*<<< orphan*/ ,int) ; 
 int pqi_report_logical_luns (struct pqi_ctrl_info*,void**) ; 
 int pqi_report_phys_luns (struct pqi_ctrl_info*,void**) ; 
 int /*<<< orphan*/  put_unaligned_be32 (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_get_device_lists(struct pqi_ctrl_info *ctrl_info,
	struct report_phys_lun_extended **physdev_list,
	struct report_log_lun_extended **logdev_list)
{
	int rc;
	size_t logdev_list_length;
	size_t logdev_data_length;
	struct report_log_lun_extended *internal_logdev_list;
	struct report_log_lun_extended *logdev_data;
	struct report_lun_header report_lun_header;

	rc = pqi_report_phys_luns(ctrl_info, (void **)physdev_list);
	if (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"report physical LUNs failed\n");

	rc = pqi_report_logical_luns(ctrl_info, (void **)logdev_list);
	if (rc)
		dev_err(&ctrl_info->pci_dev->dev,
			"report logical LUNs failed\n");

	/*
	 * Tack the controller itself onto the end of the logical device list.
	 */

	logdev_data = *logdev_list;

	if (logdev_data) {
		logdev_list_length =
			get_unaligned_be32(&logdev_data->header.list_length);
	} else {
		memset(&report_lun_header, 0, sizeof(report_lun_header));
		logdev_data =
			(struct report_log_lun_extended *)&report_lun_header;
		logdev_list_length = 0;
	}

	logdev_data_length = sizeof(struct report_lun_header) +
		logdev_list_length;

	internal_logdev_list = kmalloc(logdev_data_length +
		sizeof(struct report_log_lun_extended), GFP_KERNEL);
	if (!internal_logdev_list) {
		kfree(*logdev_list);
		*logdev_list = NULL;
		return -ENOMEM;
	}

	memcpy(internal_logdev_list, logdev_data, logdev_data_length);
	memset((u8 *)internal_logdev_list + logdev_data_length, 0,
		sizeof(struct report_log_lun_extended_entry));
	put_unaligned_be32(logdev_list_length +
		sizeof(struct report_log_lun_extended_entry),
		&internal_logdev_list->header.list_length);

	kfree(*logdev_list);
	*logdev_list = internal_logdev_list;

	return 0;
}