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
struct virtio_balloon {int dummy; } ;
struct sysinfo {unsigned long freeram; unsigned long totalram; } ;

/* Variables and functions */
 size_t HTLB_BUDDY_PGALLOC ; 
 size_t HTLB_BUDDY_PGALLOC_FAIL ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int NR_VM_EVENT_ITEMS ; 
 size_t PGFAULT ; 
 size_t PGMAJFAULT ; 
 size_t PSWPIN ; 
 size_t PSWPOUT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_AVAIL ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_CACHES ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_HTLB_PGALLOC ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_HTLB_PGFAIL ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MAJFLT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MEMFREE ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MEMTOT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MINFLT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_SWAP_IN ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_SWAP_OUT ; 
 int /*<<< orphan*/  all_vm_events (unsigned long*) ; 
 unsigned long global_node_page_state (int /*<<< orphan*/ ) ; 
 unsigned long pages_to_bytes (unsigned long) ; 
 long si_mem_available () ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int /*<<< orphan*/  update_stat (struct virtio_balloon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned int update_balloon_stats(struct virtio_balloon *vb)
{
	unsigned long events[NR_VM_EVENT_ITEMS];
	struct sysinfo i;
	unsigned int idx = 0;
	long available;
	unsigned long caches;

	all_vm_events(events);
	si_meminfo(&i);

	available = si_mem_available();
	caches = global_node_page_state(NR_FILE_PAGES);

#ifdef CONFIG_VM_EVENT_COUNTERS
	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_IN,
				pages_to_bytes(events[PSWPIN]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_OUT,
				pages_to_bytes(events[PSWPOUT]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MAJFLT, events[PGMAJFAULT]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MINFLT, events[PGFAULT]);
#ifdef CONFIG_HUGETLB_PAGE
	update_stat(vb, idx++, VIRTIO_BALLOON_S_HTLB_PGALLOC,
		    events[HTLB_BUDDY_PGALLOC]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_HTLB_PGFAIL,
		    events[HTLB_BUDDY_PGALLOC_FAIL]);
#endif
#endif
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMFREE,
				pages_to_bytes(i.freeram));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMTOT,
				pages_to_bytes(i.totalram));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_AVAIL,
				pages_to_bytes(available));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_CACHES,
				pages_to_bytes(caches));

	return idx;
}