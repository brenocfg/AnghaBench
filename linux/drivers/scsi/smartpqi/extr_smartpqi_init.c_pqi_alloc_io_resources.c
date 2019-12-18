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
struct pqi_io_request {unsigned int index; int /*<<< orphan*/  sg_chain_buffer_dma_handle; void* sg_chain_buffer; int /*<<< orphan*/  iu; } ;
struct pqi_ctrl_info {unsigned int max_io_slots; size_t sg_chain_buffer_length; TYPE_1__* pci_dev; int /*<<< orphan*/  max_inbound_iu_length; struct pqi_io_request* io_request_pool; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pqi_io_request* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_free_all_io_requests (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_alloc_io_resources(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int i;
	void *sg_chain_buffer;
	size_t sg_chain_buffer_length;
	dma_addr_t sg_chain_buffer_dma_handle;
	struct device *dev;
	struct pqi_io_request *io_request;

	ctrl_info->io_request_pool =
		kcalloc(ctrl_info->max_io_slots,
			sizeof(ctrl_info->io_request_pool[0]), GFP_KERNEL);

	if (!ctrl_info->io_request_pool) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate I/O request pool\n");
		goto error;
	}

	dev = &ctrl_info->pci_dev->dev;
	sg_chain_buffer_length = ctrl_info->sg_chain_buffer_length;
	io_request = ctrl_info->io_request_pool;

	for (i = 0; i < ctrl_info->max_io_slots; i++) {
		io_request->iu =
			kmalloc(ctrl_info->max_inbound_iu_length, GFP_KERNEL);

		if (!io_request->iu) {
			dev_err(&ctrl_info->pci_dev->dev,
				"failed to allocate IU buffers\n");
			goto error;
		}

		sg_chain_buffer = dma_alloc_coherent(dev,
			sg_chain_buffer_length, &sg_chain_buffer_dma_handle,
			GFP_KERNEL);

		if (!sg_chain_buffer) {
			dev_err(&ctrl_info->pci_dev->dev,
				"failed to allocate PQI scatter-gather chain buffers\n");
			goto error;
		}

		io_request->index = i;
		io_request->sg_chain_buffer = sg_chain_buffer;
		io_request->sg_chain_buffer_dma_handle =
			sg_chain_buffer_dma_handle;
		io_request++;
	}

	return 0;

error:
	pqi_free_all_io_requests(ctrl_info);

	return -ENOMEM;
}