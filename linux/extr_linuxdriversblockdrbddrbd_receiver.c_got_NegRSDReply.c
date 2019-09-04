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
struct packet_info {int cmd; int /*<<< orphan*/  vnr; struct p_block_ack* data; } ;
struct p_block_ack {int /*<<< orphan*/  seq_num; int /*<<< orphan*/  blksize; int /*<<< orphan*/  sector; } ;
struct drbd_peer_device {struct drbd_device* device; } ;
struct drbd_device {int dummy; } ;
struct drbd_connection {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  D_FAILED ; 
 int EIO ; 
#define  P_NEG_RS_DREPLY 129 
#define  P_RS_CANCEL 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct drbd_peer_device* conn_peer_device (struct drbd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_rs_pending (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_rs_complete_io (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_rs_failed_io (struct drbd_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  update_peer_seq (struct drbd_peer_device*,int) ; 

__attribute__((used)) static int got_NegRSDReply(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	sector_t sector;
	int size;
	struct p_block_ack *p = pi->data;

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	sector = be64_to_cpu(p->sector);
	size = be32_to_cpu(p->blksize);

	update_peer_seq(peer_device, be32_to_cpu(p->seq_num));

	dec_rs_pending(device);

	if (get_ldev_if_state(device, D_FAILED)) {
		drbd_rs_complete_io(device, sector);
		switch (pi->cmd) {
		case P_NEG_RS_DREPLY:
			drbd_rs_failed_io(device, sector, size);
		case P_RS_CANCEL:
			break;
		default:
			BUG();
		}
		put_ldev(device);
	}

	return 0;
}