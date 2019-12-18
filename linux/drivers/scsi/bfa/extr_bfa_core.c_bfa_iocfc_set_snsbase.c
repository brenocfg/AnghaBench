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
typedef  int /*<<< orphan*/  u64 ;
struct bfa_iocfc_s {TYPE_1__* cfginfo; } ;
struct bfa_s {struct bfa_iocfc_s iocfc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ioim_snsbase; scalar_t__ sense_buf_len; } ;

/* Variables and functions */
 scalar_t__ BFI_IOIM_SNSLEN ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_iocfc_set_snsbase(struct bfa_s *bfa, int seg_no, u64 snsbase_pa)
{
	struct bfa_iocfc_s	*iocfc = &bfa->iocfc;

	iocfc->cfginfo->sense_buf_len = (BFI_IOIM_SNSLEN - 1);
	bfa_dma_be_addr_set(iocfc->cfginfo->ioim_snsbase[seg_no], snsbase_pa);
}