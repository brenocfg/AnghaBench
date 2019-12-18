#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct hpt_iop_request_get_config* config; } ;
struct TYPE_5__ {TYPE_1__ mvfrey; } ;
struct hptiop_hba {TYPE_2__ u; } ;
struct TYPE_6__ {int size; scalar_t__ type; } ;
struct hpt_iop_request_get_config {int /*<<< orphan*/  sdram_size; int /*<<< orphan*/  max_devices; int /*<<< orphan*/  alignment_mask; int /*<<< orphan*/  data_transfer_length; int /*<<< orphan*/  max_sg_count; int /*<<< orphan*/  request_size; int /*<<< orphan*/  max_requests; int /*<<< orphan*/  firmware_version; int /*<<< orphan*/  interface_version; TYPE_3__ header; } ;

/* Variables and functions */
 scalar_t__ IOP_REQUEST_TYPE_GET_CONFIG ; 

__attribute__((used)) static int iop_get_config_mvfrey(struct hptiop_hba *hba,
				struct hpt_iop_request_get_config *config)
{
	struct hpt_iop_request_get_config *info = hba->u.mvfrey.config;

	if (info->header.size != sizeof(struct hpt_iop_request_get_config) ||
			info->header.type != IOP_REQUEST_TYPE_GET_CONFIG)
		return -1;

	config->interface_version = info->interface_version;
	config->firmware_version = info->firmware_version;
	config->max_requests = info->max_requests;
	config->request_size = info->request_size;
	config->max_sg_count = info->max_sg_count;
	config->data_transfer_length = info->data_transfer_length;
	config->alignment_mask = info->alignment_mask;
	config->max_devices = info->max_devices;
	config->sdram_size = info->sdram_size;

	return 0;
}