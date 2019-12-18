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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct e1000_hw_stats {int gorcl; scalar_t__ roc; int /*<<< orphan*/  prc1522; int /*<<< orphan*/  prc1023; int /*<<< orphan*/  prc511; int /*<<< orphan*/  prc255; int /*<<< orphan*/  prc127; int /*<<< orphan*/  prc64; int /*<<< orphan*/  mprc; int /*<<< orphan*/  bprc; int /*<<< orphan*/  gorch; int /*<<< orphan*/  gprc; int /*<<< orphan*/  crcerrs; } ;
struct e1000_hw {int max_frame_size; } ;

/* Variables and functions */
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void e1000_tbi_adjust_stats(struct e1000_hw *hw,
				   struct e1000_hw_stats *stats,
				   u32 frame_len, const u8 *mac_addr)
{
	u64 carry_bit;

	/* First adjust the frame length. */
	frame_len--;
	/* We need to adjust the statistics counters, since the hardware
	 * counters overcount this packet as a CRC error and undercount
	 * the packet as a good packet
	 */
	/* This packet should not be counted as a CRC error. */
	stats->crcerrs--;
	/* This packet does count as a Good Packet Received. */
	stats->gprc++;

	/* Adjust the Good Octets received counters */
	carry_bit = 0x80000000 & stats->gorcl;
	stats->gorcl += frame_len;
	/* If the high bit of Gorcl (the low 32 bits of the Good Octets
	 * Received Count) was one before the addition,
	 * AND it is zero after, then we lost the carry out,
	 * need to add one to Gorch (Good Octets Received Count High).
	 * This could be simplified if all environments supported
	 * 64-bit integers.
	 */
	if (carry_bit && ((stats->gorcl & 0x80000000) == 0))
		stats->gorch++;
	/* Is this a broadcast or multicast?  Check broadcast first,
	 * since the test for a multicast frame will test positive on
	 * a broadcast frame.
	 */
	if (is_broadcast_ether_addr(mac_addr))
		stats->bprc++;
	else if (is_multicast_ether_addr(mac_addr))
		stats->mprc++;

	if (frame_len == hw->max_frame_size) {
		/* In this case, the hardware has overcounted the number of
		 * oversize frames.
		 */
		if (stats->roc > 0)
			stats->roc--;
	}

	/* Adjust the bin counters when the extra byte put the frame in the
	 * wrong bin. Remember that the frame_len was adjusted above.
	 */
	if (frame_len == 64) {
		stats->prc64++;
		stats->prc127--;
	} else if (frame_len == 127) {
		stats->prc127++;
		stats->prc255--;
	} else if (frame_len == 255) {
		stats->prc255++;
		stats->prc511--;
	} else if (frame_len == 511) {
		stats->prc511++;
		stats->prc1023--;
	} else if (frame_len == 1023) {
		stats->prc1023++;
		stats->prc1522--;
	} else if (frame_len == 1522) {
		stats->prc1522++;
	}
}