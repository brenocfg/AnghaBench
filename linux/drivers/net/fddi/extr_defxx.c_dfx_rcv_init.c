#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_10__ {scalar_t__ rcv_prod; } ;
struct TYPE_11__ {int /*<<< orphan*/  lword; TYPE_3__ index; } ;
struct TYPE_12__ {char** p_rcv_buff_va; char* rcv_block_virt; TYPE_4__ rcv_xmt_reg; scalar_t__ rcv_bufs_to_post; scalar_t__ rcv_block_phys; TYPE_2__* descr_block_virt; int /*<<< orphan*/  bus_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_1__* rcv_data; } ;
struct TYPE_8__ {void* long_1; void* long_0; } ;
typedef  TYPE_5__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  NEW_SKB_SIZE ; 
 int PI_ALIGN_K_RCV_DATA_BUFF ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_TYPE_2_PROD ; 
 scalar_t__ PI_RCV_DATA_K_NUM_ENTRIES ; 
 int PI_RCV_DATA_K_SIZE_MAX ; 
 int PI_RCV_DESCR_M_SOP ; 
 int PI_RCV_DESCR_V_SEG_LEN ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  my_skb_align (struct sk_buff*,int) ; 

__attribute__((used)) static int dfx_rcv_init(DFX_board_t *bp, int get_buffers)
	{
	int	i, j;					/* used in for loop */

	/*
	 *  Since each receive buffer is a single fragment of same length, initialize
	 *  first longword in each receive descriptor for entire LLC Host descriptor
	 *  block.  Also initialize second longword in each receive descriptor with
	 *  physical address of receive buffer.  We'll always allocate receive
	 *  buffers in powers of 2 so that we can easily fill the 256 entry descriptor
	 *  block and produce new receive buffers by simply updating the receive
	 *  producer index.
	 *
	 * 	Assumptions:
	 *		To support all shipping versions of PDQ, the receive buffer size
	 *		must be mod 128 in length and the physical address must be 128 byte
	 *		aligned.  In other words, bits 0-6 of the length and address must
	 *		be zero for the following descriptor field entries to be correct on
	 *		all PDQ-based boards.  We guaranteed both requirements during
	 *		driver initialization when we allocated memory for the receive buffers.
	 */

	if (get_buffers) {
#ifdef DYNAMIC_BUFFERS
	for (i = 0; i < (int)(bp->rcv_bufs_to_post); i++)
		for (j = 0; (i + j) < (int)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
		{
			struct sk_buff *newskb;
			dma_addr_t dma_addr;

			newskb = __netdev_alloc_skb(bp->dev, NEW_SKB_SIZE,
						    GFP_NOIO);
			if (!newskb)
				return -ENOMEM;
			/*
			 * align to 128 bytes for compatibility with
			 * the old EISA boards.
			 */

			my_skb_align(newskb, 128);
			dma_addr = dma_map_single(bp->bus_dev,
						  newskb->data,
						  PI_RCV_DATA_K_SIZE_MAX,
						  DMA_FROM_DEVICE);
			if (dma_mapping_error(bp->bus_dev, dma_addr)) {
				dev_kfree_skb(newskb);
				return -ENOMEM;
			}
			bp->descr_block_virt->rcv_data[i + j].long_0 =
				(u32)(PI_RCV_DESCR_M_SOP |
				      ((PI_RCV_DATA_K_SIZE_MAX /
					PI_ALIGN_K_RCV_DATA_BUFF) <<
				       PI_RCV_DESCR_V_SEG_LEN));
			bp->descr_block_virt->rcv_data[i + j].long_1 =
				(u32)dma_addr;

			/*
			 * p_rcv_buff_va is only used inside the
			 * kernel so we put the skb pointer here.
			 */
			bp->p_rcv_buff_va[i+j] = (char *) newskb;
		}
#else
	for (i=0; i < (int)(bp->rcv_bufs_to_post); i++)
		for (j=0; (i + j) < (int)PI_RCV_DATA_K_NUM_ENTRIES; j += bp->rcv_bufs_to_post)
			{
			bp->descr_block_virt->rcv_data[i+j].long_0 = (u32) (PI_RCV_DESCR_M_SOP |
				((PI_RCV_DATA_K_SIZE_MAX / PI_ALIGN_K_RCV_DATA_BUFF) << PI_RCV_DESCR_V_SEG_LEN));
			bp->descr_block_virt->rcv_data[i+j].long_1 = (u32) (bp->rcv_block_phys + (i * PI_RCV_DATA_K_SIZE_MAX));
			bp->p_rcv_buff_va[i+j] = (bp->rcv_block_virt + (i * PI_RCV_DATA_K_SIZE_MAX));
			}
#endif
	}

	/* Update receive producer and Type 2 register */

	bp->rcv_xmt_reg.index.rcv_prod = bp->rcv_bufs_to_post;
	dfx_port_write_long(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);
	return 0;
	}