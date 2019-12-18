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
struct zfcp_fsf_req {int status; struct fsf_status_read_buffer* data; struct zfcp_adapter* adapter; } ;
struct TYPE_6__ {int /*<<< orphan*/  sr_data; } ;
struct zfcp_adapter {int /*<<< orphan*/  stat_work; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  stat_miss; TYPE_3__ pool; int /*<<< orphan*/  adapter_features; TYPE_1__* ccw_device; } ;
struct TYPE_5__ {int /*<<< orphan*/ * word; } ;
struct fsf_status_read_buffer {int status_type; int status_subtype; TYPE_2__ payload; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCH_EVT_LINKDOWN ; 
 int /*<<< orphan*/  FCH_EVT_LINKUP ; 
#define  FSF_STATUS_READ_BIT_ERROR_THRESHOLD 135 
#define  FSF_STATUS_READ_FEATURE_UPDATE_ALERT 134 
#define  FSF_STATUS_READ_INCOMING_ELS 133 
#define  FSF_STATUS_READ_LINK_DOWN 132 
#define  FSF_STATUS_READ_LINK_UP 131 
#define  FSF_STATUS_READ_NOTIFICATION_LOST 130 
#define  FSF_STATUS_READ_PORT_CLOSED 129 
#define  FSF_STATUS_READ_SENSE_DATA_AVAIL 128 
 int FSF_STATUS_READ_SUB_INCOMING_ELS ; 
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_FSFREQ_DISMISSED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ber_stop ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (struct fsf_status_read_buffer*) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_bit_err (char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_fsf_uss (char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_set_adapter_status (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_conditional_port_scan (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_enqueue_event (struct zfcp_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_incoming_els (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_status_read_link_down (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_status_read_port_closed (struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_status_read_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct fsf_status_read_buffer *sr_buf = req->data;

	if (req->status & ZFCP_STATUS_FSFREQ_DISMISSED) {
		zfcp_dbf_hba_fsf_uss("fssrh_1", req);
		mempool_free(virt_to_page(sr_buf), adapter->pool.sr_data);
		zfcp_fsf_req_free(req);
		return;
	}

	zfcp_dbf_hba_fsf_uss("fssrh_4", req);

	switch (sr_buf->status_type) {
	case FSF_STATUS_READ_PORT_CLOSED:
		zfcp_fsf_status_read_port_closed(req);
		break;
	case FSF_STATUS_READ_INCOMING_ELS:
		zfcp_fc_incoming_els(req);
		break;
	case FSF_STATUS_READ_SENSE_DATA_AVAIL:
		break;
	case FSF_STATUS_READ_BIT_ERROR_THRESHOLD:
		zfcp_dbf_hba_bit_err("fssrh_3", req);
		if (ber_stop) {
			dev_warn(&adapter->ccw_device->dev,
				 "All paths over this FCP device are disused because of excessive bit errors\n");
			zfcp_erp_adapter_shutdown(adapter, 0, "fssrh_b");
		} else {
			dev_warn(&adapter->ccw_device->dev,
				 "The error threshold for checksum statistics has been exceeded\n");
		}
		break;
	case FSF_STATUS_READ_LINK_DOWN:
		zfcp_fsf_status_read_link_down(req);
		zfcp_fc_enqueue_event(adapter, FCH_EVT_LINKDOWN, 0);
		break;
	case FSF_STATUS_READ_LINK_UP:
		dev_info(&adapter->ccw_device->dev,
			 "The local link has been restored\n");
		/* All ports should be marked as ready to run again */
		zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_adapter_reopen(adapter,
					ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
					ZFCP_STATUS_COMMON_ERP_FAILED,
					"fssrh_2");
		zfcp_fc_enqueue_event(adapter, FCH_EVT_LINKUP, 0);

		break;
	case FSF_STATUS_READ_NOTIFICATION_LOST:
		if (sr_buf->status_subtype & FSF_STATUS_READ_SUB_INCOMING_ELS)
			zfcp_fc_conditional_port_scan(adapter);
		break;
	case FSF_STATUS_READ_FEATURE_UPDATE_ALERT:
		adapter->adapter_features = sr_buf->payload.word[0];
		break;
	}

	mempool_free(virt_to_page(sr_buf), adapter->pool.sr_data);
	zfcp_fsf_req_free(req);

	atomic_inc(&adapter->stat_miss);
	queue_work(adapter->work_queue, &adapter->stat_work);
}