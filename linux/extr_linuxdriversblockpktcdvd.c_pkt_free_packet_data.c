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
struct packet_data {int frames; struct bio* w_bio; int /*<<< orphan*/ * pages; struct bio** r_bios; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int FRAMES_PER_PAGE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  kfree (struct packet_data*) ; 

__attribute__((used)) static void pkt_free_packet_data(struct packet_data *pkt)
{
	int i;

	for (i = 0; i < pkt->frames; i++) {
		struct bio *bio = pkt->r_bios[i];
		if (bio)
			bio_put(bio);
	}
	for (i = 0; i < pkt->frames / FRAMES_PER_PAGE; i++)
		__free_page(pkt->pages[i]);
	bio_put(pkt->w_bio);
	kfree(pkt);
}