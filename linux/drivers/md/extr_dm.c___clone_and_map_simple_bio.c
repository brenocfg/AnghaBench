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
struct bio {int dummy; } ;
struct dm_target_io {unsigned int* len_ptr; struct bio clone; } ;
struct clone_info {int /*<<< orphan*/  sector; int /*<<< orphan*/  bio; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  __bio_clone_fast (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __map_bio (struct dm_target_io*) ; 
 int /*<<< orphan*/  bio_setup_sector (struct bio*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static blk_qc_t __clone_and_map_simple_bio(struct clone_info *ci,
					   struct dm_target_io *tio, unsigned *len)
{
	struct bio *clone = &tio->clone;

	tio->len_ptr = len;

	__bio_clone_fast(clone, ci->bio);
	if (len)
		bio_setup_sector(clone, ci->sector, *len);

	return __map_bio(tio);
}