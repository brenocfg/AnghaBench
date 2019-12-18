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
struct TYPE_4__ {int /*<<< orphan*/ * req; } ;
struct TYPE_3__ {TYPE_2__ r; } ;
struct dm_crypt_io {int integrity_metadata_from_pool; int /*<<< orphan*/  io_pending; int /*<<< orphan*/ * integrity_metadata; TYPE_1__ ctx; scalar_t__ error; int /*<<< orphan*/  sector; struct bio* base_bio; struct crypt_config* cc; } ;
struct crypt_config {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypt_io_init(struct dm_crypt_io *io, struct crypt_config *cc,
			  struct bio *bio, sector_t sector)
{
	io->cc = cc;
	io->base_bio = bio;
	io->sector = sector;
	io->error = 0;
	io->ctx.r.req = NULL;
	io->integrity_metadata = NULL;
	io->integrity_metadata_from_pool = false;
	atomic_set(&io->io_pending, 0);
}