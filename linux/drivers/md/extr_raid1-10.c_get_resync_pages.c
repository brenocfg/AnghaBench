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
struct resync_pages {int dummy; } ;
struct bio {struct resync_pages* bi_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct resync_pages *get_resync_pages(struct bio *bio)
{
	return bio->bi_private;
}