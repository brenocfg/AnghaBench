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
typedef  size_t u32 ;
struct snic {int /*<<< orphan*/ * io_req_lock; } ;
struct scsi_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int SNIC_IO_LOCKS ; 
 int snic_cmd_tag (struct scsi_cmnd*) ; 

__attribute__((used)) static inline spinlock_t *
snic_io_lock_hash(struct snic *snic, struct scsi_cmnd *sc)
{
	u32 hash = snic_cmd_tag(sc) & (SNIC_IO_LOCKS - 1);

	return &snic->io_req_lock[hash];
}