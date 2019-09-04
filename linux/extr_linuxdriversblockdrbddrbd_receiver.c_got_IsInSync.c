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
struct packet_info {int /*<<< orphan*/  vnr; struct p_block_ack* data; } ;
struct p_block_ack {int /*<<< orphan*/  seq_num; int /*<<< orphan*/  blksize; int /*<<< orphan*/  sector; } ;
struct drbd_peer_device {TYPE_1__* connection; struct drbd_device* device; } ;
struct drbd_device {int rs_same_csum; int /*<<< orphan*/  rs_sect_in; } ;
struct drbd_connection {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int agreed_pro_version; } ;

/* Variables and functions */
 int BM_BLOCK_SHIFT ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct drbd_peer_device* conn_peer_device (struct drbd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_rs_pending (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_rs_complete_io (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_set_in_sync (struct drbd_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  update_peer_seq (struct drbd_peer_device*,int) ; 

__attribute__((used)) static int got_IsInSync(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct p_block_ack *p = pi->data;
	sector_t sector = be64_to_cpu(p->sector);
	int blksize = be32_to_cpu(p->blksize);

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	D_ASSERT(device, peer_device->connection->agreed_pro_version >= 89);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	if (get_ldev(device)) {
		drbd_rs_complete_io(device, sector);
		drbd_set_in_sync(device, sector, blksize);
		/* rs_same_csums is supposed to count in units of BM_BLOCK_SIZE */
		device->rs_same_csum += (blksize >> BM_BLOCK_SHIFT);
		put_ldev(device);
	}
	dec_rs_pending(device);
	atomic_add(blksize >> 9, &device->rs_sect_in);

	return 0;
}