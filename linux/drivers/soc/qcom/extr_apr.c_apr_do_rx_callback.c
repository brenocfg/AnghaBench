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
typedef  scalar_t__ uint16_t ;
struct apr_rx_buf {int len; void* buf; } ;
struct apr_hdr {scalar_t__ pkt_size; scalar_t__ src_domain; scalar_t__ dest_domain; scalar_t__ src_svc; scalar_t__ dest_svc; int /*<<< orphan*/  hdr_field; } ;
struct apr_resp_pkt {scalar_t__ payload_size; void* payload; struct apr_hdr hdr; } ;
struct apr_driver {int /*<<< orphan*/  (* callback ) (struct apr_device*,struct apr_resp_pkt*) ;} ;
struct TYPE_2__ {scalar_t__ driver; } ;
struct apr_device {TYPE_1__ dev; } ;
struct apr {int /*<<< orphan*/  dev; int /*<<< orphan*/  svcs_lock; int /*<<< orphan*/  svcs_idr; } ;

/* Variables and functions */
 scalar_t__ APR_DOMAIN_MAX ; 
 scalar_t__ APR_HDR_FIELD_MT (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_HDR_FIELD_SIZE_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_HDR_FIELD_VER (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_HDR_SIZE ; 
 scalar_t__ APR_MSG_TYPE_MAX ; 
 scalar_t__ APR_PKT_VER ; 
 scalar_t__ APR_SVC_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct apr_device* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct apr_device*,struct apr_resp_pkt*) ; 
 struct apr_driver* to_apr_driver (scalar_t__) ; 

__attribute__((used)) static int apr_do_rx_callback(struct apr *apr, struct apr_rx_buf *abuf)
{
	uint16_t hdr_size, msg_type, ver, svc_id;
	struct apr_device *svc = NULL;
	struct apr_driver *adrv = NULL;
	struct apr_resp_pkt resp;
	struct apr_hdr *hdr;
	unsigned long flags;
	void *buf = abuf->buf;
	int len = abuf->len;

	hdr = buf;
	ver = APR_HDR_FIELD_VER(hdr->hdr_field);
	if (ver > APR_PKT_VER + 1)
		return -EINVAL;

	hdr_size = APR_HDR_FIELD_SIZE_BYTES(hdr->hdr_field);
	if (hdr_size < APR_HDR_SIZE) {
		dev_err(apr->dev, "APR: Wrong hdr size:%d\n", hdr_size);
		return -EINVAL;
	}

	if (hdr->pkt_size < APR_HDR_SIZE || hdr->pkt_size != len) {
		dev_err(apr->dev, "APR: Wrong packet size\n");
		return -EINVAL;
	}

	msg_type = APR_HDR_FIELD_MT(hdr->hdr_field);
	if (msg_type >= APR_MSG_TYPE_MAX) {
		dev_err(apr->dev, "APR: Wrong message type: %d\n", msg_type);
		return -EINVAL;
	}

	if (hdr->src_domain >= APR_DOMAIN_MAX ||
			hdr->dest_domain >= APR_DOMAIN_MAX ||
			hdr->src_svc >= APR_SVC_MAX ||
			hdr->dest_svc >= APR_SVC_MAX) {
		dev_err(apr->dev, "APR: Wrong APR header\n");
		return -EINVAL;
	}

	svc_id = hdr->dest_svc;
	spin_lock_irqsave(&apr->svcs_lock, flags);
	svc = idr_find(&apr->svcs_idr, svc_id);
	if (svc && svc->dev.driver)
		adrv = to_apr_driver(svc->dev.driver);
	spin_unlock_irqrestore(&apr->svcs_lock, flags);

	if (!adrv) {
		dev_err(apr->dev, "APR: service is not registered\n");
		return -EINVAL;
	}

	resp.hdr = *hdr;
	resp.payload_size = hdr->pkt_size - hdr_size;

	/*
	 * NOTE: hdr_size is not same as APR_HDR_SIZE as remote can include
	 * optional headers in to apr_hdr which should be ignored
	 */
	if (resp.payload_size > 0)
		resp.payload = buf + hdr_size;

	adrv->callback(svc, &resp);

	return 0;
}