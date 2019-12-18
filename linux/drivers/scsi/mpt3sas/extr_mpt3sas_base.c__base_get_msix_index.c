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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int dummy; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/ * cpu_msix_table; scalar_t__ reply_queue_count; int /*<<< orphan*/  total_io_cnt; scalar_t__ msix_load_balance; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_mod64 (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t raw_smp_processor_id () ; 

__attribute__((used)) static inline u8
_base_get_msix_index(struct MPT3SAS_ADAPTER *ioc,
	struct scsi_cmnd *scmd)
{
	/* Enables reply_queue load balancing */
	if (ioc->msix_load_balance)
		return ioc->reply_queue_count ?
		    base_mod64(atomic64_add_return(1,
		    &ioc->total_io_cnt), ioc->reply_queue_count) : 0;

	return ioc->cpu_msix_table[raw_smp_processor_id()];
}