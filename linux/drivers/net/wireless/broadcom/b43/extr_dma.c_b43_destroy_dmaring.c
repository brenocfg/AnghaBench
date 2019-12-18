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
typedef  int u64 ;
struct b43_dmaring {int nr_failed_tx_packets; int nr_succeed_tx_packets; int nr_total_packet_tries; struct b43_dmaring* meta; struct b43_dmaring* txhdr_cache; int /*<<< orphan*/  nr_slots; int /*<<< orphan*/  max_used_slots; scalar_t__ type; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,unsigned int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 
 int divide (int,int) ; 
 int /*<<< orphan*/  dmacontroller_cleanup (struct b43_dmaring*) ; 
 int /*<<< orphan*/  free_all_descbuffers (struct b43_dmaring*) ; 
 int /*<<< orphan*/  free_ringmemory (struct b43_dmaring*) ; 
 int /*<<< orphan*/  kfree (struct b43_dmaring*) ; 
 scalar_t__ modulo (int,int) ; 

__attribute__((used)) static void b43_destroy_dmaring(struct b43_dmaring *ring,
				const char *ringname)
{
	if (!ring)
		return;

#ifdef CONFIG_B43_DEBUG
	{
		/* Print some statistics. */
		u64 failed_packets = ring->nr_failed_tx_packets;
		u64 succeed_packets = ring->nr_succeed_tx_packets;
		u64 nr_packets = failed_packets + succeed_packets;
		u64 permille_failed = 0, average_tries = 0;

		if (nr_packets)
			permille_failed = divide(failed_packets * 1000, nr_packets);
		if (nr_packets)
			average_tries = divide(ring->nr_total_packet_tries * 100, nr_packets);

		b43dbg(ring->dev->wl, "DMA-%u %s: "
		       "Used slots %d/%d, Failed frames %llu/%llu = %llu.%01llu%%, "
		       "Average tries %llu.%02llu\n",
		       (unsigned int)(ring->type), ringname,
		       ring->max_used_slots,
		       ring->nr_slots,
		       (unsigned long long)failed_packets,
		       (unsigned long long)nr_packets,
		       (unsigned long long)divide(permille_failed, 10),
		       (unsigned long long)modulo(permille_failed, 10),
		       (unsigned long long)divide(average_tries, 100),
		       (unsigned long long)modulo(average_tries, 100));
	}
#endif /* DEBUG */

	/* Device IRQs are disabled prior entering this function,
	 * so no need to take care of concurrency with rx handler stuff.
	 */
	dmacontroller_cleanup(ring);
	free_all_descbuffers(ring);
	free_ringmemory(ring);

	kfree(ring->txhdr_cache);
	kfree(ring->meta);
	kfree(ring);
}