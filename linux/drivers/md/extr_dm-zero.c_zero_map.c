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
struct dm_target {int dummy; } ;
struct bio {int bi_opf; } ;

/* Variables and functions */
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_SUBMITTED ; 
#define  REQ_OP_READ 129 
#define  REQ_OP_WRITE 128 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int bio_op (struct bio*) ; 
 int /*<<< orphan*/  zero_fill_bio (struct bio*) ; 

__attribute__((used)) static int zero_map(struct dm_target *ti, struct bio *bio)
{
	switch (bio_op(bio)) {
	case REQ_OP_READ:
		if (bio->bi_opf & REQ_RAHEAD) {
			/* readahead of null bytes only wastes buffer cache */
			return DM_MAPIO_KILL;
		}
		zero_fill_bio(bio);
		break;
	case REQ_OP_WRITE:
		/* writes get silently dropped */
		break;
	default:
		return DM_MAPIO_KILL;
	}

	bio_endio(bio);

	/* accepted bio, don't make new request */
	return DM_MAPIO_SUBMITTED;
}