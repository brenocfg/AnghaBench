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
struct mib_counters {int /*<<< orphan*/  rx_overrun; int /*<<< orphan*/  rx_discard; int /*<<< orphan*/  late_collision; int /*<<< orphan*/  collision; int /*<<< orphan*/  bad_crc_event; int /*<<< orphan*/  mac_receive_error; int /*<<< orphan*/  jabber_received; int /*<<< orphan*/  oversize_received; int /*<<< orphan*/  fragments_received; int /*<<< orphan*/  undersize_received; int /*<<< orphan*/  bad_fc_received; int /*<<< orphan*/  good_fc_received; int /*<<< orphan*/  fc_sent; int /*<<< orphan*/  unrec_mac_control_received; int /*<<< orphan*/  broadcast_frames_sent; int /*<<< orphan*/  multicast_frames_sent; int /*<<< orphan*/  excessive_collision; int /*<<< orphan*/  good_frames_sent; int /*<<< orphan*/  good_octets_sent; int /*<<< orphan*/  frames_1024_to_max_octets; int /*<<< orphan*/  frames_512_to_1023_octets; int /*<<< orphan*/  frames_256_to_511_octets; int /*<<< orphan*/  frames_128_to_255_octets; int /*<<< orphan*/  frames_65_to_127_octets; int /*<<< orphan*/  frames_64_octets; int /*<<< orphan*/  multicast_frames_received; int /*<<< orphan*/  broadcast_frames_received; int /*<<< orphan*/  bad_frames_received; int /*<<< orphan*/  good_frames_received; int /*<<< orphan*/  internal_mac_transmit_err; int /*<<< orphan*/  bad_octets_received; int /*<<< orphan*/  good_octets_received; } ;
struct mv643xx_eth_private {int /*<<< orphan*/  mib_counters_lock; struct mib_counters mib_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DISCARD_FRAME_CNT ; 
 int /*<<< orphan*/  RX_OVERRUN_FRAME_CNT ; 
 scalar_t__ mib_read (struct mv643xx_eth_private*,int) ; 
 scalar_t__ rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mib_counters_update(struct mv643xx_eth_private *mp)
{
	struct mib_counters *p = &mp->mib_counters;

	spin_lock_bh(&mp->mib_counters_lock);
	p->good_octets_received += mib_read(mp, 0x00);
	p->bad_octets_received += mib_read(mp, 0x08);
	p->internal_mac_transmit_err += mib_read(mp, 0x0c);
	p->good_frames_received += mib_read(mp, 0x10);
	p->bad_frames_received += mib_read(mp, 0x14);
	p->broadcast_frames_received += mib_read(mp, 0x18);
	p->multicast_frames_received += mib_read(mp, 0x1c);
	p->frames_64_octets += mib_read(mp, 0x20);
	p->frames_65_to_127_octets += mib_read(mp, 0x24);
	p->frames_128_to_255_octets += mib_read(mp, 0x28);
	p->frames_256_to_511_octets += mib_read(mp, 0x2c);
	p->frames_512_to_1023_octets += mib_read(mp, 0x30);
	p->frames_1024_to_max_octets += mib_read(mp, 0x34);
	p->good_octets_sent += mib_read(mp, 0x38);
	p->good_frames_sent += mib_read(mp, 0x40);
	p->excessive_collision += mib_read(mp, 0x44);
	p->multicast_frames_sent += mib_read(mp, 0x48);
	p->broadcast_frames_sent += mib_read(mp, 0x4c);
	p->unrec_mac_control_received += mib_read(mp, 0x50);
	p->fc_sent += mib_read(mp, 0x54);
	p->good_fc_received += mib_read(mp, 0x58);
	p->bad_fc_received += mib_read(mp, 0x5c);
	p->undersize_received += mib_read(mp, 0x60);
	p->fragments_received += mib_read(mp, 0x64);
	p->oversize_received += mib_read(mp, 0x68);
	p->jabber_received += mib_read(mp, 0x6c);
	p->mac_receive_error += mib_read(mp, 0x70);
	p->bad_crc_event += mib_read(mp, 0x74);
	p->collision += mib_read(mp, 0x78);
	p->late_collision += mib_read(mp, 0x7c);
	/* Non MIB hardware counters */
	p->rx_discard += rdlp(mp, RX_DISCARD_FRAME_CNT);
	p->rx_overrun += rdlp(mp, RX_OVERRUN_FRAME_CNT);
	spin_unlock_bh(&mp->mib_counters_lock);
}