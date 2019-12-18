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
typedef  scalar_t__ u32 ;
struct nic {scalar_t__ adaptive_ifs; int tx_frames; int tx_collisions; } ;

/* Variables and functions */
 int DUPLEX_HALF ; 
 int SPEED_100 ; 
 int /*<<< orphan*/  e100_configure ; 
 int /*<<< orphan*/  e100_exec_cb (struct nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_adjust_adaptive_ifs(struct nic *nic, int speed, int duplex)
{
	/* Adjust inter-frame-spacing (IFS) between two transmits if
	 * we're getting collisions on a half-duplex connection. */

	if (duplex == DUPLEX_HALF) {
		u32 prev = nic->adaptive_ifs;
		u32 min_frames = (speed == SPEED_100) ? 1000 : 100;

		if ((nic->tx_frames / 32 < nic->tx_collisions) &&
		   (nic->tx_frames > min_frames)) {
			if (nic->adaptive_ifs < 60)
				nic->adaptive_ifs += 5;
		} else if (nic->tx_frames < min_frames) {
			if (nic->adaptive_ifs >= 5)
				nic->adaptive_ifs -= 5;
		}
		if (nic->adaptive_ifs != prev)
			e100_exec_cb(nic, NULL, e100_configure);
	}
}