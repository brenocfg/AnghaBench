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
struct pqi_iu_layer_descriptor {int /*<<< orphan*/  outbound_spanning_supported; int /*<<< orphan*/  inbound_spanning_supported; int /*<<< orphan*/  max_inbound_iu_length; } ;
struct pqi_general_admin_response {scalar_t__ status; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_descriptor; int /*<<< orphan*/  buffer_length; } ;
struct TYPE_6__ {TYPE_2__ report_device_capability; } ;
struct TYPE_4__ {int /*<<< orphan*/  iu_length; int /*<<< orphan*/  iu_type; } ;
struct pqi_general_admin_request {TYPE_3__ data; int /*<<< orphan*/  function_code; TYPE_1__ header; } ;
struct pqi_device_capability {struct pqi_iu_layer_descriptor* iu_layer_descriptors; int /*<<< orphan*/  max_oq_element_length; int /*<<< orphan*/  max_elements_per_oq; int /*<<< orphan*/  max_outbound_queues; int /*<<< orphan*/  max_iq_element_length; int /*<<< orphan*/  max_elements_per_iq; int /*<<< orphan*/  max_inbound_queues; } ;
struct pqi_ctrl_info {int max_inbound_queues; int max_elements_per_iq; int max_iq_element_length; int max_outbound_queues; int max_elements_per_oq; int max_oq_element_length; int max_inbound_iu_length_per_firmware; int /*<<< orphan*/  outbound_spanning_supported; int /*<<< orphan*/  inbound_spanning_supported; int /*<<< orphan*/  pci_dev; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PQI_GENERAL_ADMIN_FUNCTION_REPORT_DEVICE_CAPABILITY ; 
 int /*<<< orphan*/  PQI_GENERAL_ADMIN_IU_LENGTH ; 
 scalar_t__ PQI_GENERAL_ADMIN_STATUS_SUCCESS ; 
 size_t PQI_PROTOCOL_SOP ; 
 int /*<<< orphan*/  PQI_REQUEST_IU_GENERAL_ADMIN ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pqi_device_capability*) ; 
 struct pqi_device_capability* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pqi_general_admin_request*,int /*<<< orphan*/ ,int) ; 
 int pqi_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pqi_device_capability*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pqi_submit_admin_request_synchronous (struct pqi_ctrl_info*,struct pqi_general_admin_request*,struct pqi_general_admin_response*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_report_device_capability(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct pqi_general_admin_request request;
	struct pqi_general_admin_response response;
	struct pqi_device_capability *capability;
	struct pqi_iu_layer_descriptor *sop_iu_layer_descriptor;

	capability = kmalloc(sizeof(*capability), GFP_KERNEL);
	if (!capability)
		return -ENOMEM;

	memset(&request, 0, sizeof(request));

	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code =
		PQI_GENERAL_ADMIN_FUNCTION_REPORT_DEVICE_CAPABILITY;
	put_unaligned_le32(sizeof(*capability),
		&request.data.report_device_capability.buffer_length);

	rc = pqi_map_single(ctrl_info->pci_dev,
		&request.data.report_device_capability.sg_descriptor,
		capability, sizeof(*capability),
		DMA_FROM_DEVICE);
	if (rc)
		goto out;

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);

	pqi_pci_unmap(ctrl_info->pci_dev,
		&request.data.report_device_capability.sg_descriptor, 1,
		DMA_FROM_DEVICE);

	if (rc)
		goto out;

	if (response.status != PQI_GENERAL_ADMIN_STATUS_SUCCESS) {
		rc = -EIO;
		goto out;
	}

	ctrl_info->max_inbound_queues =
		get_unaligned_le16(&capability->max_inbound_queues);
	ctrl_info->max_elements_per_iq =
		get_unaligned_le16(&capability->max_elements_per_iq);
	ctrl_info->max_iq_element_length =
		get_unaligned_le16(&capability->max_iq_element_length)
		* 16;
	ctrl_info->max_outbound_queues =
		get_unaligned_le16(&capability->max_outbound_queues);
	ctrl_info->max_elements_per_oq =
		get_unaligned_le16(&capability->max_elements_per_oq);
	ctrl_info->max_oq_element_length =
		get_unaligned_le16(&capability->max_oq_element_length)
		* 16;

	sop_iu_layer_descriptor =
		&capability->iu_layer_descriptors[PQI_PROTOCOL_SOP];

	ctrl_info->max_inbound_iu_length_per_firmware =
		get_unaligned_le16(
			&sop_iu_layer_descriptor->max_inbound_iu_length);
	ctrl_info->inbound_spanning_supported =
		sop_iu_layer_descriptor->inbound_spanning_supported;
	ctrl_info->outbound_spanning_supported =
		sop_iu_layer_descriptor->outbound_spanning_supported;

out:
	kfree(capability);

	return rc;
}