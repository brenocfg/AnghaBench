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
typedef  unsigned int u32 ;
struct hpdi_private {unsigned int dma_desc_phys_addr; unsigned int* dio_buffer_phys_addr; unsigned int num_dma_descriptors; unsigned int block_size; TYPE_1__* dma_desc; scalar_t__* dio_buffer; scalar_t__* desc_dio_buffer; } ;
struct comedi_device {struct hpdi_private* private; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_2__ {void* next; void* transfer_size; void* local_start_addr; void* pci_start_addr; } ;

/* Variables and functions */
 unsigned int DMA_BUFFER_SIZE ; 
 int EINVAL ; 
 unsigned int FIFO_REG ; 
 unsigned int NUM_DMA_BUFFERS ; 
 unsigned int NUM_DMA_DESCRIPTORS ; 
 unsigned int PLX_DMADPR_DESCPCI ; 
 unsigned int PLX_DMADPR_TCINTR ; 
 unsigned int PLX_DMADPR_XFERL2P ; 
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static int gsc_hpdi_setup_dma_descriptors(struct comedi_device *dev,
					  unsigned int len)
{
	struct hpdi_private *devpriv = dev->private;
	dma_addr_t phys_addr = devpriv->dma_desc_phys_addr;
	u32 next_bits = PLX_DMADPR_DESCPCI | PLX_DMADPR_TCINTR |
			PLX_DMADPR_XFERL2P;
	unsigned int offset = 0;
	unsigned int idx = 0;
	unsigned int i;

	if (len > DMA_BUFFER_SIZE)
		len = DMA_BUFFER_SIZE;
	len -= len % sizeof(u32);
	if (len == 0)
		return -EINVAL;

	for (i = 0; i < NUM_DMA_DESCRIPTORS && idx < NUM_DMA_BUFFERS; i++) {
		devpriv->dma_desc[i].pci_start_addr =
		    cpu_to_le32(devpriv->dio_buffer_phys_addr[idx] + offset);
		devpriv->dma_desc[i].local_start_addr = cpu_to_le32(FIFO_REG);
		devpriv->dma_desc[i].transfer_size = cpu_to_le32(len);
		devpriv->dma_desc[i].next = cpu_to_le32((phys_addr +
			(i + 1) * sizeof(devpriv->dma_desc[0])) | next_bits);

		devpriv->desc_dio_buffer[i] = devpriv->dio_buffer[idx] +
					      (offset / sizeof(u32));

		offset += len;
		if (len + offset > DMA_BUFFER_SIZE) {
			offset = 0;
			idx++;
		}
	}
	devpriv->num_dma_descriptors = i;
	/* fix last descriptor to point back to first */
	devpriv->dma_desc[i - 1].next = cpu_to_le32(phys_addr | next_bits);

	devpriv->block_size = len;

	return len;
}