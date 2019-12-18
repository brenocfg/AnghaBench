#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* ioctl_data; int ioctl_len; int /*<<< orphan*/  ioctl_busaddr; TYPE_1__* pcidev; } ;
typedef  TYPE_2__ ips_ha_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_alloc_passthru_buffer(ips_ha_t * ha, int length)
{
	void *bigger_buf;
	dma_addr_t dma_busaddr;

	if (ha->ioctl_data && length <= ha->ioctl_len)
		return 0;
	/* there is no buffer or it's not big enough, allocate a new one */
	bigger_buf = dma_alloc_coherent(&ha->pcidev->dev, length, &dma_busaddr,
			GFP_KERNEL);
	if (bigger_buf) {
		/* free the old memory */
		dma_free_coherent(&ha->pcidev->dev, ha->ioctl_len,
				  ha->ioctl_data, ha->ioctl_busaddr);
		/* use the new memory */
		ha->ioctl_data = (char *) bigger_buf;
		ha->ioctl_len = length;
		ha->ioctl_busaddr = dma_busaddr;
	} else {
		return -1;
	}
	return 0;
}