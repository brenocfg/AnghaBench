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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct vscsiif_request {size_t rqid; int nr_segments; scalar_t__ cmd_len; int timeout_per_command; int /*<<< orphan*/ * seg; scalar_t__ sc_data_direction; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  channel; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  ref_rqid; int /*<<< orphan*/  act; } ;
struct vscsiif_front_ring {int /*<<< orphan*/  req_prod_pvt; } ;
struct vscsifrnt_shadow {size_t rqid; int nr_segments; int /*<<< orphan*/ * seg; int /*<<< orphan*/  ref_rqid; int /*<<< orphan*/  act; struct scsi_cmnd* sc; } ;
struct vscsifrnt_info {int /*<<< orphan*/  irq; struct vscsiif_front_ring ring; struct vscsifrnt_shadow** shadow; } ;
struct scsi_cmnd {scalar_t__ cmd_len; TYPE_2__* request; scalar_t__ sc_data_direction; int /*<<< orphan*/  cmnd; TYPE_1__* device; } ;
struct TYPE_4__ {int timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int HZ ; 
 scalar_t__ RING_FULL (struct vscsiif_front_ring*) ; 
 struct vscsiif_request* RING_GET_REQUEST (struct vscsiif_front_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (struct vscsiif_front_ring*,int) ; 
 scalar_t__ VSCSIIF_MAX_COMMAND_SIZE ; 
 size_t VSCSIIF_MAX_REQS ; 
 int VSCSIIF_SG_GRANT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 size_t scsifront_get_rqid (struct vscsifrnt_info*) ; 

__attribute__((used)) static int scsifront_do_request(struct vscsifrnt_info *info,
				struct vscsifrnt_shadow *shadow)
{
	struct vscsiif_front_ring *ring = &(info->ring);
	struct vscsiif_request *ring_req;
	struct scsi_cmnd *sc = shadow->sc;
	uint32_t id;
	int i, notify;

	if (RING_FULL(&info->ring))
		return -EBUSY;

	id = scsifront_get_rqid(info);	/* use id in response */
	if (id >= VSCSIIF_MAX_REQS)
		return -EBUSY;

	info->shadow[id] = shadow;
	shadow->rqid = id;

	ring_req = RING_GET_REQUEST(&(info->ring), ring->req_prod_pvt);
	ring->req_prod_pvt++;

	ring_req->rqid        = id;
	ring_req->act         = shadow->act;
	ring_req->ref_rqid    = shadow->ref_rqid;
	ring_req->nr_segments = shadow->nr_segments;

	ring_req->id      = sc->device->id;
	ring_req->lun     = sc->device->lun;
	ring_req->channel = sc->device->channel;
	ring_req->cmd_len = sc->cmd_len;

	BUG_ON(sc->cmd_len > VSCSIIF_MAX_COMMAND_SIZE);

	memcpy(ring_req->cmnd, sc->cmnd, sc->cmd_len);

	ring_req->sc_data_direction   = (uint8_t)sc->sc_data_direction;
	ring_req->timeout_per_command = sc->request->timeout / HZ;

	for (i = 0; i < (shadow->nr_segments & ~VSCSIIF_SG_GRANT); i++)
		ring_req->seg[i] = shadow->seg[i];

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(ring, notify);
	if (notify)
		notify_remote_via_irq(info->irq);

	return 0;
}