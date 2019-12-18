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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct hwrm_nvm_read_input {void* len; void* offset; int /*<<< orphan*/  dir_idx; int /*<<< orphan*/  host_dest_addr; int /*<<< orphan*/  member_0; } ;
struct bnxt {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_NVM_READ ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_nvm_read_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_nvm_read_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,unsigned int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_nvram_item(struct net_device *dev, u32 index, u32 offset,
			       u32 length, u8 *data)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;
	u8 *buf;
	dma_addr_t dma_handle;
	struct hwrm_nvm_read_input req = {0};

	if (!length)
		return -EINVAL;

	buf = dma_alloc_coherent(&bp->pdev->dev, length, &dma_handle,
				 GFP_KERNEL);
	if (!buf) {
		netdev_err(dev, "dma_alloc_coherent failure, length = %u\n",
			   (unsigned)length);
		return -ENOMEM;
	}
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_NVM_READ, -1, -1);
	req.host_dest_addr = cpu_to_le64(dma_handle);
	req.dir_idx = cpu_to_le16(index);
	req.offset = cpu_to_le32(offset);
	req.len = cpu_to_le32(length);

	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc == 0)
		memcpy(data, buf, length);
	dma_free_coherent(&bp->pdev->dev, length, buf, dma_handle);
	return rc;
}