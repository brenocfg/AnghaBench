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
struct clone {unsigned long region_shift; } ;
struct TYPE_2__ {unsigned long bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long bio_to_region(struct clone *clone, struct bio *bio)
{
	return (bio->bi_iter.bi_sector >> clone->region_shift);
}