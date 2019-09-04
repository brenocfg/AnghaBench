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
struct request_queue {int dummy; } ;
struct TYPE_2__ {int size; } ;
struct pktcdvd_device {int /*<<< orphan*/  flags; TYPE_1__ settings; } ;

/* Variables and functions */
 int CD_FRAMESIZE ; 
 int EIO ; 
 int /*<<< orphan*/  PACKET_MERGE_SEGS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*) ; 
 int queue_max_segments (struct request_queue*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkt_set_segment_merging(struct pktcdvd_device *pd, struct request_queue *q)
{
	if ((pd->settings.size << 9) / CD_FRAMESIZE
	    <= queue_max_segments(q)) {
		/*
		 * The cdrom device can handle one segment/frame
		 */
		clear_bit(PACKET_MERGE_SEGS, &pd->flags);
		return 0;
	} else if ((pd->settings.size << 9) / PAGE_SIZE
		   <= queue_max_segments(q)) {
		/*
		 * We can handle this case at the expense of some extra memory
		 * copies during write operations
		 */
		set_bit(PACKET_MERGE_SEGS, &pd->flags);
		return 0;
	} else {
		pkt_err(pd, "cdrom max_phys_segments too small\n");
		return -EIO;
	}
}