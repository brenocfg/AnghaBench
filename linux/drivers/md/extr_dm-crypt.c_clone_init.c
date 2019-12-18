#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_crypt_io {TYPE_2__* base_bio; struct crypt_config* cc; } ;
struct crypt_config {TYPE_1__* dev; } ;
struct bio {int /*<<< orphan*/  bi_opf; int /*<<< orphan*/  bi_end_io; struct dm_crypt_io* bi_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_opf; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_endio ; 

__attribute__((used)) static void clone_init(struct dm_crypt_io *io, struct bio *clone)
{
	struct crypt_config *cc = io->cc;

	clone->bi_private = io;
	clone->bi_end_io  = crypt_endio;
	bio_set_dev(clone, cc->dev->bdev);
	clone->bi_opf	  = io->base_bio->bi_opf;
}