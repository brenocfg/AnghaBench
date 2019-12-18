#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct scsi_cmnd {TYPE_1__* request; } ;
struct fnic {int /*<<< orphan*/ * io_req_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int tag; } ;

/* Variables and functions */
 int FNIC_IO_LOCKS ; 

__attribute__((used)) static inline spinlock_t *fnic_io_lock_hash(struct fnic *fnic,
					    struct scsi_cmnd *sc)
{
	u32 hash = sc->request->tag & (FNIC_IO_LOCKS - 1);

	return &fnic->io_req_lock[hash];
}