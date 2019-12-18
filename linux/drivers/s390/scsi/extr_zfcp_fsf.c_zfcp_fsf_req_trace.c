#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct zfcp_latency_cont {int /*<<< orphan*/  counter; int /*<<< orphan*/  fabric; int /*<<< orphan*/  channel; } ;
struct TYPE_17__ {int /*<<< orphan*/  lock; struct zfcp_latency_cont cmd; struct zfcp_latency_cont write; struct zfcp_latency_cont read; } ;
struct zfcp_scsi_dev {TYPE_8__ latencies; } ;
struct TYPE_12__ {int /*<<< orphan*/  qdio_outb_usage; } ;
struct zfcp_fsf_req {int status; TYPE_7__* qtcb; TYPE_4__* adapter; TYPE_3__ qdio_req; } ;
struct zfcp_blk_drv_data {int channel_lat; int fabric_lat; int /*<<< orphan*/  flags; int /*<<< orphan*/  outb_usage; scalar_t__ inb_usage; int /*<<< orphan*/  magic; } ;
struct scsi_cmnd {TYPE_9__* request; int /*<<< orphan*/  device; } ;
struct fsf_qual_latency_info {int channel_lat; int fabric_lat; } ;
typedef  int /*<<< orphan*/  blktrc ;
struct TYPE_18__ {int /*<<< orphan*/  q; } ;
struct TYPE_14__ {int data_direction; } ;
struct TYPE_15__ {TYPE_5__ io; } ;
struct TYPE_10__ {struct fsf_qual_latency_info latency_info; } ;
struct TYPE_11__ {TYPE_1__ prot_status_qual; } ;
struct TYPE_16__ {TYPE_6__ bottom; TYPE_2__ prefix; } ;
struct TYPE_13__ {int timer_ticks; int adapter_features; } ;

/* Variables and functions */
#define  FSF_DATADIR_CMND 134 
#define  FSF_DATADIR_DIF_READ_CONVERT 133 
#define  FSF_DATADIR_DIF_READ_STRIP 132 
#define  FSF_DATADIR_DIF_WRITE_CONVERT 131 
#define  FSF_DATADIR_DIF_WRITE_INSERT 130 
#define  FSF_DATADIR_READ 129 
#define  FSF_DATADIR_WRITE 128 
 int FSF_FEATURE_MEASUREMENT_DATA ; 
 int /*<<< orphan*/  ZFCP_BLK_DRV_DATA_MAGIC ; 
 int /*<<< orphan*/  ZFCP_BLK_LAT_VALID ; 
 int /*<<< orphan*/  ZFCP_BLK_REQ_ERROR ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  blk_add_driver_data (int /*<<< orphan*/ ,TYPE_9__*,struct zfcp_blk_drv_data*,int) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_update_lat (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void zfcp_fsf_req_trace(struct zfcp_fsf_req *req, struct scsi_cmnd *scsi)
{
	struct fsf_qual_latency_info *lat_in;
	struct zfcp_latency_cont *lat = NULL;
	struct zfcp_scsi_dev *zfcp_sdev;
	struct zfcp_blk_drv_data blktrc;
	int ticks = req->adapter->timer_ticks;

	lat_in = &req->qtcb->prefix.prot_status_qual.latency_info;

	blktrc.flags = 0;
	blktrc.magic = ZFCP_BLK_DRV_DATA_MAGIC;
	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		blktrc.flags |= ZFCP_BLK_REQ_ERROR;
	blktrc.inb_usage = 0;
	blktrc.outb_usage = req->qdio_req.qdio_outb_usage;

	if (req->adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA &&
	    !(req->status & ZFCP_STATUS_FSFREQ_ERROR)) {
		zfcp_sdev = sdev_to_zfcp(scsi->device);
		blktrc.flags |= ZFCP_BLK_LAT_VALID;
		blktrc.channel_lat = lat_in->channel_lat * ticks;
		blktrc.fabric_lat = lat_in->fabric_lat * ticks;

		switch (req->qtcb->bottom.io.data_direction) {
		case FSF_DATADIR_DIF_READ_STRIP:
		case FSF_DATADIR_DIF_READ_CONVERT:
		case FSF_DATADIR_READ:
			lat = &zfcp_sdev->latencies.read;
			break;
		case FSF_DATADIR_DIF_WRITE_INSERT:
		case FSF_DATADIR_DIF_WRITE_CONVERT:
		case FSF_DATADIR_WRITE:
			lat = &zfcp_sdev->latencies.write;
			break;
		case FSF_DATADIR_CMND:
			lat = &zfcp_sdev->latencies.cmd;
			break;
		}

		if (lat) {
			spin_lock(&zfcp_sdev->latencies.lock);
			zfcp_fsf_update_lat(&lat->channel, lat_in->channel_lat);
			zfcp_fsf_update_lat(&lat->fabric, lat_in->fabric_lat);
			lat->counter++;
			spin_unlock(&zfcp_sdev->latencies.lock);
		}
	}

	blk_add_driver_data(scsi->request->q, scsi->request, &blktrc,
			    sizeof(blktrc));
}