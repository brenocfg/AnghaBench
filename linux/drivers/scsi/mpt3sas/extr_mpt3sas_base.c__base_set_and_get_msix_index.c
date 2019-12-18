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
typedef  scalar_t__ u16 ;
struct scsiio_tracker {int /*<<< orphan*/  msix_io; int /*<<< orphan*/  scmd; } ;
struct MPT3SAS_ADAPTER {scalar_t__ hi_priority_smid; int /*<<< orphan*/  (* get_msix_index_for_smlio ) (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _base_get_msix_index (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ; 
 struct scsiio_tracker* _get_st_from_smid (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
_base_set_and_get_msix_index(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	struct scsiio_tracker *st = NULL;

	if (smid < ioc->hi_priority_smid)
		st = _get_st_from_smid(ioc, smid);

	if (st == NULL)
		return  _base_get_msix_index(ioc, NULL);

	st->msix_io = ioc->get_msix_index_for_smlio(ioc, st->scmd);
	return st->msix_io;
}