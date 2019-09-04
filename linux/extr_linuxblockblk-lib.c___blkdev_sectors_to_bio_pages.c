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
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ BIO_MAX_PAGES ; 
 int /*<<< orphan*/  DIV_ROUND_UP_SECTOR_T (int /*<<< orphan*/ ,int) ; 
 int PAGE_SIZE ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __blkdev_sectors_to_bio_pages(sector_t nr_sects)
{
	sector_t pages = DIV_ROUND_UP_SECTOR_T(nr_sects, PAGE_SIZE / 512);

	return min(pages, (sector_t)BIO_MAX_PAGES);
}