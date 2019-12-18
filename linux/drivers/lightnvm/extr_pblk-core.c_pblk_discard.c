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
struct pblk {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_get_lba (struct bio*) ; 
 int /*<<< orphan*/  pblk_get_secs (struct bio*) ; 
 int /*<<< orphan*/  pblk_invalidate_range (struct pblk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pblk_discard(struct pblk *pblk, struct bio *bio)
{
	sector_t slba = pblk_get_lba(bio);
	sector_t nr_secs = pblk_get_secs(bio);

	pblk_invalidate_range(pblk, slba, nr_secs);
}