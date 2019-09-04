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
struct hd_struct {int /*<<< orphan*/  partno; scalar_t__ policy; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_devname (struct bio*,char*) ; 
 int bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ op_is_write (int const) ; 

__attribute__((used)) static inline bool bio_check_ro(struct bio *bio, struct hd_struct *part)
{
	const int op = bio_op(bio);

	if (part->policy && op_is_write(op)) {
		char b[BDEVNAME_SIZE];

		if (op_is_flush(bio->bi_opf) && !bio_sectors(bio))
			return false;

		WARN_ONCE(1,
		       "generic_make_request: Trying to write "
			"to read-only block-device %s (partno %d)\n",
			bio_devname(bio, b), part->partno);
		/* Older lvm-tools actually trigger this */
		return false;
	}

	return false;
}