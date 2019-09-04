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
typedef  int /*<<< orphan*/  u64 ;
struct drbd_peer_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int _drbd_send_ack (struct drbd_peer_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

int drbd_send_ack_ex(struct drbd_peer_device *peer_device, enum drbd_packet cmd,
		     sector_t sector, int blksize, u64 block_id)
{
	return _drbd_send_ack(peer_device, cmd,
			      cpu_to_be64(sector),
			      cpu_to_be32(blksize),
			      cpu_to_be64(block_id));
}