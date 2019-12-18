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
struct scsiio_tracker {int smid; int cb_idx; int /*<<< orphan*/ * scmd; scalar_t__ direct_io; } ;
struct MPT3SAS_ADAPTER {TYPE_1__* chain_lookup; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain_offset; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mpt3sas_base_clear_st(struct MPT3SAS_ADAPTER *ioc,
			   struct scsiio_tracker *st)
{
	if (WARN_ON(st->smid == 0))
		return;
	st->cb_idx = 0xFF;
	st->direct_io = 0;
	st->scmd = NULL;
	atomic_set(&ioc->chain_lookup[st->smid - 1].chain_offset, 0);
	st->smid = 0;
}