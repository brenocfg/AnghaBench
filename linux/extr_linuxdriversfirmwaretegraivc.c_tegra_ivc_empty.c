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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct tegra_ivc_header {TYPE_2__ rx; TYPE_1__ tx; } ;
struct tegra_ivc {scalar_t__ num_frames; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tegra_ivc_empty(struct tegra_ivc *ivc,
				   struct tegra_ivc_header *header)
{
	/*
	 * This function performs multiple checks on the same values with
	 * security implications, so create snapshots with READ_ONCE() to
	 * ensure that these checks use the same values.
	 */
	u32 tx = READ_ONCE(header->tx.count);
	u32 rx = READ_ONCE(header->rx.count);

	/*
	 * Perform an over-full check to prevent denial of service attacks
	 * where a server could be easily fooled into believing that there's
	 * an extremely large number of frames ready, since receivers are not
	 * expected to check for full or over-full conditions.
	 *
	 * Although the channel isn't empty, this is an invalid case caused by
	 * a potentially malicious peer, so returning empty is safer, because
	 * it gives the impression that the channel has gone silent.
	 */
	if (tx - rx > ivc->num_frames)
		return true;

	return tx == rx;
}