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
struct i40e_stats {int dummy; } ;
struct i40e_ring {int /*<<< orphan*/  syncp; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct i40e_stats*) ; 
 int /*<<< orphan*/  i40e_add_one_ethtool_stat (int /*<<< orphan*/ *,struct i40e_ring*,struct i40e_stats const*) ; 
 struct i40e_stats* i40e_gstrings_queue_stats ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
i40e_add_queue_stats(u64 **data, struct i40e_ring *ring)
{
	const unsigned int size = ARRAY_SIZE(i40e_gstrings_queue_stats);
	const struct i40e_stats *stats = i40e_gstrings_queue_stats;
	unsigned int start;
	unsigned int i;

	/* To avoid invalid statistics values, ensure that we keep retrying
	 * the copy until we get a consistent value according to
	 * u64_stats_fetch_retry_irq. But first, make sure our ring is
	 * non-null before attempting to access its syncp.
	 */
	do {
		start = !ring ? 0 : u64_stats_fetch_begin_irq(&ring->syncp);
		for (i = 0; i < size; i++) {
			i40e_add_one_ethtool_stat(&(*data)[i], ring,
						  &stats[i]);
		}
	} while (ring && u64_stats_fetch_retry_irq(&ring->syncp, start));

	/* Once we successfully copy the stats in, update the data pointer */
	*data += size;
}