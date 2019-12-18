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
struct request {int dummy; } ;
struct mapped_device {int /*<<< orphan*/  init_tio_pdu; } ;
struct dm_rq_target_io {int /*<<< orphan*/  info; scalar_t__ completed; scalar_t__ error; struct request* orig; int /*<<< orphan*/ * clone; int /*<<< orphan*/ * ti; struct mapped_device* md; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_tio(struct dm_rq_target_io *tio, struct request *rq,
		     struct mapped_device *md)
{
	tio->md = md;
	tio->ti = NULL;
	tio->clone = NULL;
	tio->orig = rq;
	tio->error = 0;
	tio->completed = 0;
	/*
	 * Avoid initializing info for blk-mq; it passes
	 * target-specific data through info.ptr
	 * (see: dm_mq_init_request)
	 */
	if (!md->init_tio_pdu)
		memset(&tio->info, 0, sizeof(tio->info));
}