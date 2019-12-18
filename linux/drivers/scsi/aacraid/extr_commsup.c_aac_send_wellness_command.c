#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sgmap64 {TYPE_2__* sg; void* count; } ;
struct fib {int dummy; } ;
struct aac_srb {int /*<<< orphan*/  sg; int /*<<< orphan*/ * cdb; void* count; void* cdb_size; scalar_t__ retry_limit; void* timeout; void* flags; scalar_t__ lun; void* id; void* channel; void* function; } ;
struct TYPE_4__ {int /*<<< orphan*/  virt_device_target; int /*<<< orphan*/  virt_device_bus; } ;
struct aac_dev {TYPE_3__* pdev; TYPE_1__ supplement_adapter_info; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {void* count; void** addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_OUT ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SRBF_ExecuteScsi ; 
 int SRB_DataOut ; 
 int /*<<< orphan*/  ScsiPortCommand64 ; 
 int /*<<< orphan*/  WRITE_HOST_WELLNESS ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 char* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,char*,int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aac_send_wellness_command(struct aac_dev *dev, char *wellness_str,
							u32 datasize)
{
	struct aac_srb *srbcmd;
	struct sgmap64 *sg64;
	dma_addr_t addr;
	char *dma_buf;
	struct fib *fibptr;
	int ret = -ENOMEM;
	u32 vbus, vid;

	fibptr = aac_fib_alloc(dev);
	if (!fibptr)
		goto out;

	dma_buf = dma_alloc_coherent(&dev->pdev->dev, datasize, &addr,
				     GFP_KERNEL);
	if (!dma_buf)
		goto fib_free_out;

	aac_fib_init(fibptr);

	vbus = (u32)le16_to_cpu(dev->supplement_adapter_info.virt_device_bus);
	vid = (u32)le16_to_cpu(dev->supplement_adapter_info.virt_device_target);

	srbcmd = (struct aac_srb *)fib_data(fibptr);

	srbcmd->function = cpu_to_le32(SRBF_ExecuteScsi);
	srbcmd->channel = cpu_to_le32(vbus);
	srbcmd->id = cpu_to_le32(vid);
	srbcmd->lun = 0;
	srbcmd->flags = cpu_to_le32(SRB_DataOut);
	srbcmd->timeout = cpu_to_le32(10);
	srbcmd->retry_limit = 0;
	srbcmd->cdb_size = cpu_to_le32(12);
	srbcmd->count = cpu_to_le32(datasize);

	memset(srbcmd->cdb, 0, sizeof(srbcmd->cdb));
	srbcmd->cdb[0] = BMIC_OUT;
	srbcmd->cdb[6] = WRITE_HOST_WELLNESS;
	memcpy(dma_buf, (char *)wellness_str, datasize);

	sg64 = (struct sgmap64 *)&srbcmd->sg;
	sg64->count = cpu_to_le32(1);
	sg64->sg[0].addr[1] = cpu_to_le32((u32)(((addr) >> 16) >> 16));
	sg64->sg[0].addr[0] = cpu_to_le32((u32)(addr & 0xffffffff));
	sg64->sg[0].count = cpu_to_le32(datasize);

	ret = aac_fib_send(ScsiPortCommand64, fibptr, sizeof(struct aac_srb),
				FsaNormal, 1, 1, NULL, NULL);

	dma_free_coherent(&dev->pdev->dev, datasize, dma_buf, addr);

	/*
	 * Do not set XferState to zero unless
	 * receives a response from F/W
	 */
	if (ret >= 0)
		aac_fib_complete(fibptr);

	/*
	 * FIB should be freed only after
	 * getting the response from the F/W
	 */
	if (ret != -ERESTARTSYS)
		goto fib_free_out;

out:
	return ret;
fib_free_out:
	aac_fib_free(fibptr);
	goto out;
}