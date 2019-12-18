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
struct mirror {int dummy; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */

__attribute__((used)) static void bio_set_m(struct bio *bio, struct mirror *m)
{
	bio->bi_next = (struct bio *) m;
}