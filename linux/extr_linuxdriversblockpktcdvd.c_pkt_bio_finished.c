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
struct TYPE_4__ {int /*<<< orphan*/  attention; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending_bios; } ;
struct pktcdvd_device {int /*<<< orphan*/  wqueue; TYPE_2__ iosched; TYPE_1__ cdrw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_bio_finished(struct pktcdvd_device *pd)
{
	BUG_ON(atomic_read(&pd->cdrw.pending_bios) <= 0);
	if (atomic_dec_and_test(&pd->cdrw.pending_bios)) {
		pkt_dbg(2, pd, "queue empty\n");
		atomic_set(&pd->iosched.attention, 1);
		wake_up(&pd->wqueue);
	}
}