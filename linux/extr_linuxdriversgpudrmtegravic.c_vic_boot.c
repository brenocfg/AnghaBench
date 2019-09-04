#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int paddr; void* vaddr; } ;
struct TYPE_6__ {TYPE_1__ firmware; } ;
struct vic {int booted; int /*<<< orphan*/  dev; TYPE_2__ falcon; } ;

/* Variables and functions */
 int CG_IDLE_CG_DLY_CNT (int) ; 
 int CG_IDLE_CG_EN ; 
 int CG_WAKEUP_DLY_CNT (int) ; 
 int FCE_UCODE_SIZE_OFFSET ; 
 int /*<<< orphan*/  NV_PVIC_MISC_PRI_VIC_CG ; 
 int /*<<< orphan*/  VIC_SET_APPLICATION_ID ; 
 int /*<<< orphan*/  VIC_SET_FCE_UCODE_OFFSET ; 
 int /*<<< orphan*/  VIC_SET_FCE_UCODE_SIZE ; 
 int VIC_UCODE_FCE_DATA_OFFSET ; 
 int VIC_UCODE_FCE_HEADER_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int falcon_boot (TYPE_2__*) ; 
 int /*<<< orphan*/  falcon_execute_method (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int falcon_wait_idle (TYPE_2__*) ; 
 int /*<<< orphan*/  vic_writel (struct vic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vic_boot(struct vic *vic)
{
	u32 fce_ucode_size, fce_bin_data_offset;
	void *hdr;
	int err = 0;

	if (vic->booted)
		return 0;

	/* setup clockgating registers */
	vic_writel(vic, CG_IDLE_CG_DLY_CNT(4) |
			CG_IDLE_CG_EN |
			CG_WAKEUP_DLY_CNT(4),
		   NV_PVIC_MISC_PRI_VIC_CG);

	err = falcon_boot(&vic->falcon);
	if (err < 0)
		return err;

	hdr = vic->falcon.firmware.vaddr;
	fce_bin_data_offset = *(u32 *)(hdr + VIC_UCODE_FCE_DATA_OFFSET);
	hdr = vic->falcon.firmware.vaddr +
		*(u32 *)(hdr + VIC_UCODE_FCE_HEADER_OFFSET);
	fce_ucode_size = *(u32 *)(hdr + FCE_UCODE_SIZE_OFFSET);

	falcon_execute_method(&vic->falcon, VIC_SET_APPLICATION_ID, 1);
	falcon_execute_method(&vic->falcon, VIC_SET_FCE_UCODE_SIZE,
			      fce_ucode_size);
	falcon_execute_method(&vic->falcon, VIC_SET_FCE_UCODE_OFFSET,
			      (vic->falcon.firmware.paddr + fce_bin_data_offset)
				>> 8);

	err = falcon_wait_idle(&vic->falcon);
	if (err < 0) {
		dev_err(vic->dev,
			"failed to set application ID and FCE base\n");
		return err;
	}

	vic->booted = true;

	return 0;
}