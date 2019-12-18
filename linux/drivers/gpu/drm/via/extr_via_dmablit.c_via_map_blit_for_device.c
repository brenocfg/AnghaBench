#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {unsigned int descriptors_per_page; int chain_start; int num_desc; int /*<<< orphan*/  state; TYPE_3__** desc_pages; int /*<<< orphan*/  direction; int /*<<< orphan*/ * pages; } ;
typedef  TYPE_1__ drm_via_sg_info_t ;
struct TYPE_8__ {unsigned char* mem_addr; unsigned int fb_addr; int num_lines; unsigned long line_length; scalar_t__ fb_stride; int /*<<< orphan*/  mem_stride; } ;
typedef  TYPE_2__ drm_via_dmablit_t ;
struct TYPE_9__ {unsigned int dev_addr; unsigned int size; unsigned int next; int /*<<< orphan*/  mem_addr; } ;
typedef  TYPE_3__ drm_via_descriptor_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ PAGE_SIZE ; 
 int VIA_DMA_DPR_EC ; 
 size_t VIA_PFN (unsigned char*) ; 
 scalar_t__ VIA_PGDN (unsigned char*) ; 
 scalar_t__ VIA_PGOFF (unsigned char*) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_map_single (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_via_device_mapped ; 
 unsigned int min (scalar_t__,unsigned long) ; 

__attribute__((used)) static void
via_map_blit_for_device(struct pci_dev *pdev,
		   const drm_via_dmablit_t *xfer,
		   drm_via_sg_info_t *vsg,
		   int mode)
{
	unsigned cur_descriptor_page = 0;
	unsigned num_descriptors_this_page = 0;
	unsigned char *mem_addr = xfer->mem_addr;
	unsigned char *cur_mem;
	unsigned char *first_addr = (unsigned char *)VIA_PGDN(mem_addr);
	uint32_t fb_addr = xfer->fb_addr;
	uint32_t cur_fb;
	unsigned long line_len;
	unsigned remaining_len;
	int num_desc = 0;
	int cur_line;
	dma_addr_t next = 0 | VIA_DMA_DPR_EC;
	drm_via_descriptor_t *desc_ptr = NULL;

	if (mode == 1)
		desc_ptr = vsg->desc_pages[cur_descriptor_page];

	for (cur_line = 0; cur_line < xfer->num_lines; ++cur_line) {

		line_len = xfer->line_length;
		cur_fb = fb_addr;
		cur_mem = mem_addr;

		while (line_len > 0) {

			remaining_len = min(PAGE_SIZE-VIA_PGOFF(cur_mem), line_len);
			line_len -= remaining_len;

			if (mode == 1) {
				desc_ptr->mem_addr =
					dma_map_page(&pdev->dev,
						     vsg->pages[VIA_PFN(cur_mem) -
								VIA_PFN(first_addr)],
						     VIA_PGOFF(cur_mem), remaining_len,
						     vsg->direction);
				desc_ptr->dev_addr = cur_fb;

				desc_ptr->size = remaining_len;
				desc_ptr->next = (uint32_t) next;
				next = dma_map_single(&pdev->dev, desc_ptr, sizeof(*desc_ptr),
						      DMA_TO_DEVICE);
				desc_ptr++;
				if (++num_descriptors_this_page >= vsg->descriptors_per_page) {
					num_descriptors_this_page = 0;
					desc_ptr = vsg->desc_pages[++cur_descriptor_page];
				}
			}

			num_desc++;
			cur_mem += remaining_len;
			cur_fb += remaining_len;
		}

		mem_addr += xfer->mem_stride;
		fb_addr += xfer->fb_stride;
	}

	if (mode == 1) {
		vsg->chain_start = next;
		vsg->state = dr_via_device_mapped;
	}
	vsg->num_desc = num_desc;
}