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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * dbuf_kva; int /*<<< orphan*/  dbuf_pa; } ;
struct bfa_diag_s {TYPE_1__ fwping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_DIAG_DMA_BUF_SZ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_diag_memclaim(struct bfa_diag_s *diag, u8 *dm_kva, u64 dm_pa)
{
	diag->fwping.dbuf_kva = dm_kva;
	diag->fwping.dbuf_pa = dm_pa;
	memset(diag->fwping.dbuf_kva, 0, BFI_DIAG_DMA_BUF_SZ);
}