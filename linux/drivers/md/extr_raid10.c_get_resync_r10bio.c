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
struct r10bio {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct r10bio* raid_bio; } ;

/* Variables and functions */
 TYPE_1__* get_resync_pages (struct bio*) ; 

__attribute__((used)) static inline struct r10bio *get_resync_r10bio(struct bio *bio)
{
	return get_resync_pages(bio)->raid_bio;
}