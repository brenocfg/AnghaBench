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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct slimpro_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_buffer; TYPE_1__ adapter; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SLIMPRO_IIC_BUS ; 
 int SLIMPRO_IIC_ENCODE_ADDR (int) ; 
 int SLIMPRO_IIC_ENCODE_FLAG_BUFADDR ; 
 int SLIMPRO_IIC_ENCODE_FLAG_WITH_DATA_LEN (int) ; 
 int SLIMPRO_IIC_ENCODE_MSG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int SLIMPRO_IIC_ENCODE_UPPER_BUFADDR (scalar_t__) ; 
 int /*<<< orphan*/  SLIMPRO_IIC_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int slimpro_i2c_send_msg (struct slimpro_i2c_dev*,int*,int*) ; 

__attribute__((used)) static int slimpro_i2c_blkrd(struct slimpro_i2c_dev *ctx, u32 chip, u32 addr,
			     u32 addrlen, u32 protocol, u32 readlen,
			     u32 with_data_len, void *data)
{
	dma_addr_t paddr;
	u32 msg[3];
	int rc;

	paddr = dma_map_single(ctx->dev, ctx->dma_buffer, readlen, DMA_FROM_DEVICE);
	if (dma_mapping_error(ctx->dev, paddr)) {
		dev_err(&ctx->adapter.dev, "Error in mapping dma buffer %p\n",
			ctx->dma_buffer);
		return -ENOMEM;
	}

	msg[0] = SLIMPRO_IIC_ENCODE_MSG(SLIMPRO_IIC_BUS, chip, SLIMPRO_IIC_READ,
					protocol, addrlen, readlen);
	msg[1] = SLIMPRO_IIC_ENCODE_FLAG_BUFADDR |
		 SLIMPRO_IIC_ENCODE_FLAG_WITH_DATA_LEN(with_data_len) |
		 SLIMPRO_IIC_ENCODE_UPPER_BUFADDR(paddr) |
		 SLIMPRO_IIC_ENCODE_ADDR(addr);
	msg[2] = (u32)paddr;

	rc = slimpro_i2c_send_msg(ctx, msg, msg);

	/* Copy to destination */
	memcpy(data, ctx->dma_buffer, readlen);

	dma_unmap_single(ctx->dev, paddr, readlen, DMA_FROM_DEVICE);
	return rc;
}