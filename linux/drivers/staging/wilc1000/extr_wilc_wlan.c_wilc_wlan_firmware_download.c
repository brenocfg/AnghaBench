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
typedef  size_t u32 ;
struct wilc {TYPE_1__* hif_func; } ;
struct TYPE_2__ {int (* hif_block_tx ) (struct wilc*,size_t,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 size_t BIT (int) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WILC_BUS_ACQUIRE_ONLY ; 
 int /*<<< orphan*/  WILC_BUS_RELEASE_ONLY ; 
 int /*<<< orphan*/  acquire_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 size_t get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  release_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int stub1 (struct wilc*,size_t,int /*<<< orphan*/ *,size_t) ; 

int wilc_wlan_firmware_download(struct wilc *wilc, const u8 *buffer,
				u32 buffer_size)
{
	u32 offset;
	u32 addr, size, size2, blksz;
	u8 *dma_buffer;
	int ret = 0;

	blksz = BIT(12);

	dma_buffer = kmalloc(blksz, GFP_KERNEL);
	if (!dma_buffer)
		return -EIO;

	offset = 0;
	do {
		addr = get_unaligned_le32(&buffer[offset]);
		size = get_unaligned_le32(&buffer[offset + 4]);
		acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
		offset += 8;
		while (((int)size) && (offset < buffer_size)) {
			if (size <= blksz)
				size2 = size;
			else
				size2 = blksz;

			memcpy(dma_buffer, &buffer[offset], size2);
			ret = wilc->hif_func->hif_block_tx(wilc, addr,
							   dma_buffer, size2);
			if (!ret)
				break;

			addr += size2;
			offset += size2;
			size -= size2;
		}
		release_bus(wilc, WILC_BUS_RELEASE_ONLY);

		if (!ret) {
			ret = -EIO;
			goto fail;
		}
	} while (offset < buffer_size);

fail:

	kfree(dma_buffer);

	return (ret < 0) ? ret : 0;
}