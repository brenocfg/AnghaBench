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
struct dm_verity_io {int /*<<< orphan*/  v; } ;
struct dm_verity_fec_io {scalar_t__ level; int /*<<< orphan*/ * output; scalar_t__ nbufs; int /*<<< orphan*/  bufs; int /*<<< orphan*/ * rs; } ;

/* Variables and functions */
 struct dm_verity_fec_io* fec_io (struct dm_verity_io*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verity_fec_is_enabled (int /*<<< orphan*/ ) ; 

void verity_fec_init_io(struct dm_verity_io *io)
{
	struct dm_verity_fec_io *fio = fec_io(io);

	if (!verity_fec_is_enabled(io->v))
		return;

	fio->rs = NULL;
	memset(fio->bufs, 0, sizeof(fio->bufs));
	fio->nbufs = 0;
	fio->output = NULL;
	fio->level = 0;
}