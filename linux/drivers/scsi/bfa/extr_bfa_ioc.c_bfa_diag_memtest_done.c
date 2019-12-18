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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  smem_page_start; int /*<<< orphan*/  host_page_num_fn; int /*<<< orphan*/  smem_pg0; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
struct bfa_diag_s {scalar_t__ block; int /*<<< orphan*/  status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ timer_active; struct bfa_diag_memtest_result* result; struct bfa_ioc_s* ioc; } ;
struct bfa_diag_memtest_result {scalar_t__ status; scalar_t__ addr; scalar_t__ exp; scalar_t__ act; scalar_t__ err_status; scalar_t__ err_status1; scalar_t__ err_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_MEMTEST_FAILED ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int BFI_BOOT_MEMTEST_RES_ADDR ; 
 scalar_t__ BFI_BOOT_MEMTEST_RES_SIG ; 
 int PSS_SMEM_PGNUM (int /*<<< orphan*/ ,int) ; 
 int PSS_SMEM_PGOFF (int) ; 
 int /*<<< orphan*/  bfa_ioc_reset_fwstate (struct bfa_ioc_s*) ; 
 int bfa_mem_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* swab32 (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_diag_memtest_done(void *cbarg)
{
	struct bfa_diag_s *diag = cbarg;
	struct bfa_ioc_s  *ioc = diag->ioc;
	struct bfa_diag_memtest_result *res = diag->result;
	u32	loff = BFI_BOOT_MEMTEST_RES_ADDR;
	u32	pgnum, pgoff, i;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	pgoff = PSS_SMEM_PGOFF(loff);

	writel(pgnum, ioc->ioc_regs.host_page_num_fn);

	for (i = 0; i < (sizeof(struct bfa_diag_memtest_result) /
			 sizeof(u32)); i++) {
		/* read test result from smem */
		*((u32 *) res + i) =
			bfa_mem_read(ioc->ioc_regs.smem_page_start, loff);
		loff += sizeof(u32);
	}

	/* Reset IOC fwstates to BFI_IOC_UNINIT */
	bfa_ioc_reset_fwstate(ioc);

	res->status = swab32(res->status);
	bfa_trc(diag, res->status);

	if (res->status == BFI_BOOT_MEMTEST_RES_SIG)
		diag->status = BFA_STATUS_OK;
	else {
		diag->status = BFA_STATUS_MEMTEST_FAILED;
		res->addr = swab32(res->addr);
		res->exp = swab32(res->exp);
		res->act = swab32(res->act);
		res->err_status = swab32(res->err_status);
		res->err_status1 = swab32(res->err_status1);
		res->err_addr = swab32(res->err_addr);
		bfa_trc(diag, res->addr);
		bfa_trc(diag, res->exp);
		bfa_trc(diag, res->act);
		bfa_trc(diag, res->err_status);
		bfa_trc(diag, res->err_status1);
		bfa_trc(diag, res->err_addr);
	}
	diag->timer_active = 0;
	diag->cbfn(diag->cbarg, diag->status);
	diag->block = 0;
}