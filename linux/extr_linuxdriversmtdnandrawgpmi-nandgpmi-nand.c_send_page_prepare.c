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
struct gpmi_nand_data {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 scalar_t__ virt_addr_valid (void const*) ; 

__attribute__((used)) static int send_page_prepare(struct gpmi_nand_data *this,
			const void *source, unsigned length,
			void *alt_virt, dma_addr_t alt_phys, unsigned alt_size,
			const void **use_virt, dma_addr_t *use_phys)
{
	struct device *dev = this->dev;

	if (virt_addr_valid(source)) {
		dma_addr_t source_phys;

		source_phys = dma_map_single(dev, (void *)source, length,
						DMA_TO_DEVICE);
		if (dma_mapping_error(dev, source_phys)) {
			if (alt_size < length) {
				dev_err(dev, "Alternate buffer is too small\n");
				return -ENOMEM;
			}
			goto map_failed;
		}
		*use_virt = source;
		*use_phys = source_phys;
		return 0;
	}
map_failed:
	/*
	 * Copy the content of the source buffer into the alternate
	 * buffer and set up the return values accordingly.
	 */
	memcpy(alt_virt, source, length);

	*use_virt = alt_virt;
	*use_phys = alt_phys;
	return 0;
}