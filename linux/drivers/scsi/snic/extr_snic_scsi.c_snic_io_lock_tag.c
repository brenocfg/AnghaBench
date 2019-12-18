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
struct snic {int /*<<< orphan*/ * io_req_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int SNIC_IO_LOCKS ; 

__attribute__((used)) static inline spinlock_t *
snic_io_lock_tag(struct snic *snic, int tag)
{
	return &snic->io_req_lock[tag & (SNIC_IO_LOCKS - 1)];
}