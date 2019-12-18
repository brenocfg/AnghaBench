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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct fib {int hbacmd_size; scalar_t__ hw_error_pa; scalar_t__ hw_fib_va; } ;
struct aac_hba_reset_req {void* error_length; void* error_ptr_lo; void* error_ptr_hi; int /*<<< orphan*/  it_nexus; } ;
struct aac_hba_map_info {int /*<<< orphan*/  rmw_nexus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ERROR_BUFFER_SIZE ; 
 int /*<<< orphan*/  HBA_IU_TYPE_SATA_REQ ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aac_hba_reset_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 aac_eh_tmf_hard_reset_fib(struct aac_hba_map_info *info,
				    struct fib *fib)
{
	struct aac_hba_reset_req *rst;
	u64 address;

	/* already tried, start a hard reset now */
	rst = (struct aac_hba_reset_req *)fib->hw_fib_va;
	memset(rst, 0, sizeof(*rst));
	rst->it_nexus = info->rmw_nexus;

	address = (u64)fib->hw_error_pa;
	rst->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
	rst->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
	rst->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);
	fib->hbacmd_size = sizeof(*rst);

       return HBA_IU_TYPE_SATA_REQ;
}