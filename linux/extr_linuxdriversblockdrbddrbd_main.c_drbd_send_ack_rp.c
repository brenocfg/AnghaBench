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
struct p_block_req {int /*<<< orphan*/  block_id; int /*<<< orphan*/  blksize; int /*<<< orphan*/  sector; } ;
struct drbd_peer_device {int dummy; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int /*<<< orphan*/  _drbd_send_ack (struct drbd_peer_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drbd_send_ack_rp(struct drbd_peer_device *peer_device, enum drbd_packet cmd,
		      struct p_block_req *rp)
{
	_drbd_send_ack(peer_device, cmd, rp->sector, rp->blksize, rp->block_id);
}