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
struct fwnet_packet_task {TYPE_2__* dev; } ;
struct fw_card {int dummy; } ;
struct TYPE_4__ {TYPE_1__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  fwnet_transmit_packet_done (struct fwnet_packet_task*) ; 
 int /*<<< orphan*/  fwnet_transmit_packet_failed (struct fwnet_packet_task*) ; 
 scalar_t__ printk_timed_ratelimit (unsigned long*,int) ; 

__attribute__((used)) static void fwnet_write_complete(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct fwnet_packet_task *ptask = data;
	static unsigned long j;
	static int last_rcode, errors_skipped;

	if (rcode == RCODE_COMPLETE) {
		fwnet_transmit_packet_done(ptask);
	} else {
		if (printk_timed_ratelimit(&j,  1000) || rcode != last_rcode) {
			dev_err(&ptask->dev->netdev->dev,
				"fwnet_write_complete failed: %x (skipped %d)\n",
				rcode, errors_skipped);

			errors_skipped = 0;
			last_rcode = rcode;
		} else {
			errors_skipped++;
		}
		fwnet_transmit_packet_failed(ptask);
	}
}