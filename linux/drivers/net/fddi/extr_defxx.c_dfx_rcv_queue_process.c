#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
typedef  int dma_addr_t ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {scalar_t__ rcv_comp; int rcv_prod; } ;
struct TYPE_17__ {TYPE_5__ index; } ;
struct TYPE_19__ {char** p_rcv_buff_va; TYPE_6__ rcv_xmt_reg; int /*<<< orphan*/  rcv_multicast_frames; int /*<<< orphan*/  rcv_total_frames; int /*<<< orphan*/  rcv_total_bytes; TYPE_9__* dev; int /*<<< orphan*/  bus_dev; int /*<<< orphan*/  rcv_discards; TYPE_4__* descr_block_virt; int /*<<< orphan*/  rcv_length_errors; int /*<<< orphan*/  rcv_frame_status_errors; int /*<<< orphan*/  rcv_crc_errors; TYPE_1__* cons_block_virt; } ;
struct TYPE_13__ {scalar_t__ rcv_cons; } ;
struct TYPE_18__ {TYPE_2__ index; } ;
struct TYPE_15__ {TYPE_3__* rcv_data; } ;
struct TYPE_14__ {int long_1; } ;
struct TYPE_12__ {int /*<<< orphan*/  xmt_rcv_data; } ;
typedef  TYPE_7__ PI_TYPE_2_CONSUMER ;
typedef  TYPE_8__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FDDI_K_LLC_LEN ; 
 int /*<<< orphan*/  FDDI_K_LLC_ZLEN ; 
 int /*<<< orphan*/  IN_RANGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NEW_SKB_SIZE ; 
 int PI_FMC_DESCR_M_LEN ; 
 int PI_FMC_DESCR_M_RCC_CRC ; 
 int PI_FMC_DESCR_M_RCC_FLUSH ; 
 int PI_FMC_DESCR_V_LEN ; 
 int /*<<< orphan*/  PI_RCV_DATA_K_SIZE_MAX ; 
 int RCV_BUFF_K_DA ; 
 int RCV_BUFF_K_DESCR ; 
 int RCV_BUFF_K_PADDING ; 
 int SKBUFF_RX_COPYBREAK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fddi_type_trans (struct sk_buff*,TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  my_skb_align (struct sk_buff*,int) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_9__*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void dfx_rcv_queue_process(
	DFX_board_t *bp
	)

	{
	PI_TYPE_2_CONSUMER	*p_type_2_cons;		/* ptr to rcv/xmt consumer block register */
	char				*p_buff;			/* ptr to start of packet receive buffer (FMC descriptor) */
	u32					descr, pkt_len;		/* FMC descriptor field and packet length */
	struct sk_buff		*skb = NULL;			/* pointer to a sk_buff to hold incoming packet data */

	/* Service all consumed LLC receive frames */

	p_type_2_cons = (PI_TYPE_2_CONSUMER *)(&bp->cons_block_virt->xmt_rcv_data);
	while (bp->rcv_xmt_reg.index.rcv_comp != p_type_2_cons->index.rcv_cons)
		{
		/* Process any errors */
		dma_addr_t dma_addr;
		int entry;

		entry = bp->rcv_xmt_reg.index.rcv_comp;
#ifdef DYNAMIC_BUFFERS
		p_buff = (char *) (((struct sk_buff *)bp->p_rcv_buff_va[entry])->data);
#else
		p_buff = bp->p_rcv_buff_va[entry];
#endif
		dma_addr = bp->descr_block_virt->rcv_data[entry].long_1;
		dma_sync_single_for_cpu(bp->bus_dev,
					dma_addr + RCV_BUFF_K_DESCR,
					sizeof(u32),
					DMA_FROM_DEVICE);
		memcpy(&descr, p_buff + RCV_BUFF_K_DESCR, sizeof(u32));

		if (descr & PI_FMC_DESCR_M_RCC_FLUSH)
			{
			if (descr & PI_FMC_DESCR_M_RCC_CRC)
				bp->rcv_crc_errors++;
			else
				bp->rcv_frame_status_errors++;
			}
		else
		{
			int rx_in_place = 0;

			/* The frame was received without errors - verify packet length */

			pkt_len = (u32)((descr & PI_FMC_DESCR_M_LEN) >> PI_FMC_DESCR_V_LEN);
			pkt_len -= 4;				/* subtract 4 byte CRC */
			if (!IN_RANGE(pkt_len, FDDI_K_LLC_ZLEN, FDDI_K_LLC_LEN))
				bp->rcv_length_errors++;
			else{
#ifdef DYNAMIC_BUFFERS
				struct sk_buff *newskb = NULL;

				if (pkt_len > SKBUFF_RX_COPYBREAK) {
					dma_addr_t new_dma_addr;

					newskb = netdev_alloc_skb(bp->dev,
								  NEW_SKB_SIZE);
					if (newskb){
						my_skb_align(newskb, 128);
						new_dma_addr = dma_map_single(
								bp->bus_dev,
								newskb->data,
								PI_RCV_DATA_K_SIZE_MAX,
								DMA_FROM_DEVICE);
						if (dma_mapping_error(
								bp->bus_dev,
								new_dma_addr)) {
							dev_kfree_skb(newskb);
							newskb = NULL;
						}
					}
					if (newskb) {
						rx_in_place = 1;

						skb = (struct sk_buff *)bp->p_rcv_buff_va[entry];
						dma_unmap_single(bp->bus_dev,
							dma_addr,
							PI_RCV_DATA_K_SIZE_MAX,
							DMA_FROM_DEVICE);
						skb_reserve(skb, RCV_BUFF_K_PADDING);
						bp->p_rcv_buff_va[entry] = (char *)newskb;
						bp->descr_block_virt->rcv_data[entry].long_1 = (u32)new_dma_addr;
					}
				}
				if (!newskb)
#endif
					/* Alloc new buffer to pass up,
					 * add room for PRH. */
					skb = netdev_alloc_skb(bp->dev,
							       pkt_len + 3);
				if (skb == NULL)
					{
					printk("%s: Could not allocate receive buffer.  Dropping packet.\n", bp->dev->name);
					bp->rcv_discards++;
					break;
					}
				else {
					if (!rx_in_place) {
						/* Receive buffer allocated, pass receive packet up */
						dma_sync_single_for_cpu(
							bp->bus_dev,
							dma_addr +
							RCV_BUFF_K_PADDING,
							pkt_len + 3,
							DMA_FROM_DEVICE);

						skb_copy_to_linear_data(skb,
							       p_buff + RCV_BUFF_K_PADDING,
							       pkt_len + 3);
					}

					skb_reserve(skb,3);		/* adjust data field so that it points to FC byte */
					skb_put(skb, pkt_len);		/* pass up packet length, NOT including CRC */
					skb->protocol = fddi_type_trans(skb, bp->dev);
					bp->rcv_total_bytes += skb->len;
					netif_rx(skb);

					/* Update the rcv counters */
					bp->rcv_total_frames++;
					if (*(p_buff + RCV_BUFF_K_DA) & 0x01)
						bp->rcv_multicast_frames++;
				}
			}
			}

		/*
		 * Advance the producer (for recycling) and advance the completion
		 * (for servicing received frames).  Note that it is okay to
		 * advance the producer without checking that it passes the
		 * completion index because they are both advanced at the same
		 * rate.
		 */

		bp->rcv_xmt_reg.index.rcv_prod += 1;
		bp->rcv_xmt_reg.index.rcv_comp += 1;
		}
	}