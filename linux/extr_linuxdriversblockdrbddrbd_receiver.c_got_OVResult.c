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
struct packet_info {int /*<<< orphan*/  vnr; struct p_block_ack* data; } ;
struct p_block_ack {int /*<<< orphan*/  block_id; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  blksize; int /*<<< orphan*/  sector; } ;
struct drbd_peer_device {TYPE_1__* connection; struct drbd_device* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  cb; } ;
struct drbd_device_work {TYPE_2__ w; struct drbd_device* device; } ;
struct drbd_device {int ov_left; } ;
struct drbd_connection {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_3__ {int /*<<< orphan*/  sender_work; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ ID_OUT_OF_SYNC ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct drbd_peer_device* conn_peer_device (struct drbd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_rs_pending (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_advance_rs_marks (struct drbd_device*,int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_ov_out_of_sync_found (struct drbd_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  drbd_queue_work (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  drbd_resync_finished (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_rs_complete_io (struct drbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  get_ldev (struct drbd_device*) ; 
 struct drbd_device_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_out_of_sync_print (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  update_peer_seq (struct drbd_peer_device*,int) ; 
 int /*<<< orphan*/  w_ov_finished ; 

__attribute__((used)) static int got_OVResult(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct p_block_ack *p = pi->data;
	struct drbd_device_work *dw;
	sector_t sector;
	int size;

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	if (be64_to_cpu(p->block_id) == ID_OUT_OF_SYNC)
		drbd_ov_out_of_sync_found(device, sector, size);
	else
		ov_out_of_sync_print(device);

	if (!get_ldev(device))
		return 0;

	drbd_rs_complete_io(device, sector);
	dec_rs_pending(device);

	--device->ov_left;

	/* let's advance progress step marks only for every other megabyte */
	if ((device->ov_left & 0x200) == 0x200)
		drbd_advance_rs_marks(device, device->ov_left);

	if (device->ov_left == 0) {
		dw = kmalloc(sizeof(*dw), GFP_NOIO);
		if (dw) {
			dw->w.cb = w_ov_finished;
			dw->device = device;
			drbd_queue_work(&peer_device->connection->sender_work, &dw->w);
		} else {
			drbd_err(device, "kmalloc(dw) failed.");
			ov_out_of_sync_print(device);
			drbd_resync_finished(device);
		}
	}
	put_ldev(device);
	return 0;
}