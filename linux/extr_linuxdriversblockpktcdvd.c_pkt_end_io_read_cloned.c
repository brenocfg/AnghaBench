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
struct pktcdvd_device {int dummy; } ;
struct packet_stacked_data {TYPE_1__* bio; struct pktcdvd_device* pd; } ;
struct bio {int /*<<< orphan*/  bi_status; struct packet_stacked_data* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (TYPE_1__*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  mempool_free (struct packet_stacked_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_bio_finished (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  psd_pool ; 

__attribute__((used)) static void pkt_end_io_read_cloned(struct bio *bio)
{
	struct packet_stacked_data *psd = bio->bi_private;
	struct pktcdvd_device *pd = psd->pd;

	psd->bio->bi_status = bio->bi_status;
	bio_put(bio);
	bio_endio(psd->bio);
	mempool_free(psd, &psd_pool);
	pkt_bio_finished(pd);
}