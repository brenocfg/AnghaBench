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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vnic_dev {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INIT_PROV_INFO2 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int vnic_dev_init_prov2(struct vnic_dev *vdev, u8 *buf, u32 len)
{
	u64 a0, a1 = len;
	int wait = 1000;
	dma_addr_t prov_pa;
	void *prov_buf;
	int ret;

	prov_buf = pci_alloc_consistent(vdev->pdev, len, &prov_pa);
	if (!prov_buf)
		return -ENOMEM;

	memcpy(prov_buf, buf, len);

	a0 = prov_pa;

	ret = vnic_dev_cmd(vdev, CMD_INIT_PROV_INFO2, &a0, &a1, wait);

	pci_free_consistent(vdev->pdev, len, prov_buf, prov_pa);

	return ret;
}