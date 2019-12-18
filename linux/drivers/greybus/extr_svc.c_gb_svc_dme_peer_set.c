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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct gb_svc_dme_peer_set_response {int /*<<< orphan*/  result_code; } ;
struct gb_svc_dme_peer_set_request {int /*<<< orphan*/  value; void* selector; void* attr; int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  GB_SVC_TYPE_DME_PEER_SET ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_dme_peer_set_request*,int,struct gb_svc_dme_peer_set_response*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

int gb_svc_dme_peer_set(struct gb_svc *svc, u8 intf_id, u16 attr, u16 selector,
			u32 value)
{
	struct gb_svc_dme_peer_set_request request;
	struct gb_svc_dme_peer_set_response response;
	u16 result;
	int ret;

	request.intf_id = intf_id;
	request.attr = cpu_to_le16(attr);
	request.selector = cpu_to_le16(selector);
	request.value = cpu_to_le32(value);

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_DME_PEER_SET,
				&request, sizeof(request),
				&response, sizeof(response));
	if (ret) {
		dev_err(&svc->dev, "failed to set DME attribute (%u 0x%04x %u %u): %d\n",
			intf_id, attr, selector, value, ret);
		return ret;
	}

	result = le16_to_cpu(response.result_code);
	if (result) {
		dev_err(&svc->dev, "UniPro error while setting DME attribute (%u 0x%04x %u %u): %u\n",
			intf_id, attr, selector, value, result);
		return -EREMOTEIO;
	}

	return 0;
}