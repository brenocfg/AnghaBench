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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct rx_status_block {int dummy; } ;
struct rx_ring {int psr_entries; size_t ps_ring_physaddr; size_t rx_status_bus; int /*<<< orphan*/  recv_list; int /*<<< orphan*/  num_rfd; void* rx_status_block; void* ps_ring_virtaddr; struct fbr_lookup** fbr; } ;
struct pkt_stat_desc {int dummy; } ;
struct fbr_lookup {int buffsize; int num_entries; size_t ring_physaddr; size_t* mem_physaddrs; size_t** virt; int /*<<< orphan*/ * bus_low; int /*<<< orphan*/ * bus_high; void** mem_virtaddrs; void* ring_virtaddr; } ;
struct fbr_desc {int dummy; } ;
struct et131x_adapter {int registry_jumbo_packet; TYPE_1__* pdev; struct rx_ring rx_ring; } ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t FBR_CHUNKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIC_DEFAULT_NUM_RFD ; 
 size_t NUM_FBRS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,size_t*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (size_t) ; 
 int /*<<< orphan*/  upper_32_bits (size_t) ; 

__attribute__((used)) static int et131x_rx_dma_memory_alloc(struct et131x_adapter *adapter)
{
	u8 id;
	u32 i, j;
	u32 bufsize;
	u32 psr_size;
	u32 fbr_chunksize;
	struct rx_ring *rx_ring = &adapter->rx_ring;
	struct fbr_lookup *fbr;

	/* Alloc memory for the lookup table */
	rx_ring->fbr[0] = kzalloc(sizeof(*fbr), GFP_KERNEL);
	if (rx_ring->fbr[0] == NULL)
		return -ENOMEM;
	rx_ring->fbr[1] = kzalloc(sizeof(*fbr), GFP_KERNEL);
	if (rx_ring->fbr[1] == NULL)
		return -ENOMEM;

	/* The first thing we will do is configure the sizes of the buffer
	 * rings. These will change based on jumbo packet support.  Larger
	 * jumbo packets increases the size of each entry in FBR0, and the
	 * number of entries in FBR0, while at the same time decreasing the
	 * number of entries in FBR1.
	 *
	 * FBR1 holds "large" frames, FBR0 holds "small" frames.  If FBR1
	 * entries are huge in order to accommodate a "jumbo" frame, then it
	 * will have less entries.  Conversely, FBR1 will now be relied upon
	 * to carry more "normal" frames, thus it's entry size also increases
	 * and the number of entries goes up too (since it now carries
	 * "small" + "regular" packets.
	 *
	 * In this scheme, we try to maintain 512 entries between the two
	 * rings. Also, FBR1 remains a constant size - when it's size doubles
	 * the number of entries halves.  FBR0 increases in size, however.
	 */
	if (adapter->registry_jumbo_packet < 2048) {
		rx_ring->fbr[0]->buffsize = 256;
		rx_ring->fbr[0]->num_entries = 512;
		rx_ring->fbr[1]->buffsize = 2048;
		rx_ring->fbr[1]->num_entries = 512;
	} else if (adapter->registry_jumbo_packet < 4096) {
		rx_ring->fbr[0]->buffsize = 512;
		rx_ring->fbr[0]->num_entries = 1024;
		rx_ring->fbr[1]->buffsize = 4096;
		rx_ring->fbr[1]->num_entries = 512;
	} else {
		rx_ring->fbr[0]->buffsize = 1024;
		rx_ring->fbr[0]->num_entries = 768;
		rx_ring->fbr[1]->buffsize = 16384;
		rx_ring->fbr[1]->num_entries = 128;
	}

	rx_ring->psr_entries = rx_ring->fbr[0]->num_entries +
			       rx_ring->fbr[1]->num_entries;

	for (id = 0; id < NUM_FBRS; id++) {
		fbr = rx_ring->fbr[id];
		/* Allocate an area of memory for Free Buffer Ring */
		bufsize = sizeof(struct fbr_desc) * fbr->num_entries;
		fbr->ring_virtaddr = dma_alloc_coherent(&adapter->pdev->dev,
							bufsize,
							&fbr->ring_physaddr,
							GFP_KERNEL);
		if (!fbr->ring_virtaddr) {
			dev_err(&adapter->pdev->dev,
				"Cannot alloc memory for Free Buffer Ring %d\n",
				id);
			return -ENOMEM;
		}
	}

	for (id = 0; id < NUM_FBRS; id++) {
		fbr = rx_ring->fbr[id];
		fbr_chunksize = (FBR_CHUNKS * fbr->buffsize);

		for (i = 0; i < fbr->num_entries / FBR_CHUNKS; i++) {
			dma_addr_t fbr_physaddr;

			fbr->mem_virtaddrs[i] = dma_alloc_coherent(
					&adapter->pdev->dev, fbr_chunksize,
					&fbr->mem_physaddrs[i],
					GFP_KERNEL);

			if (!fbr->mem_virtaddrs[i]) {
				dev_err(&adapter->pdev->dev,
					"Could not alloc memory\n");
				return -ENOMEM;
			}

			/* See NOTE in "Save Physical Address" comment above */
			fbr_physaddr = fbr->mem_physaddrs[i];

			for (j = 0; j < FBR_CHUNKS; j++) {
				u32 k = (i * FBR_CHUNKS) + j;

				/* Save the Virtual address of this index for
				 * quick access later
				 */
				fbr->virt[k] = (u8 *)fbr->mem_virtaddrs[i] +
						   (j * fbr->buffsize);

				/* now store the physical address in the
				 * descriptor so the device can access it
				 */
				fbr->bus_high[k] = upper_32_bits(fbr_physaddr);
				fbr->bus_low[k] = lower_32_bits(fbr_physaddr);
				fbr_physaddr += fbr->buffsize;
			}
		}
	}

	/* Allocate an area of memory for FIFO of Packet Status ring entries */
	psr_size = sizeof(struct pkt_stat_desc) * rx_ring->psr_entries;

	rx_ring->ps_ring_virtaddr = dma_alloc_coherent(&adapter->pdev->dev,
						  psr_size,
						  &rx_ring->ps_ring_physaddr,
						  GFP_KERNEL);

	if (!rx_ring->ps_ring_virtaddr) {
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Packet Status Ring\n");
		return -ENOMEM;
	}

	/* Allocate an area of memory for writeback of status information */
	rx_ring->rx_status_block = dma_alloc_coherent(&adapter->pdev->dev,
					    sizeof(struct rx_status_block),
					    &rx_ring->rx_status_bus,
					    GFP_KERNEL);
	if (!rx_ring->rx_status_block) {
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Status Block\n");
		return -ENOMEM;
	}
	rx_ring->num_rfd = NIC_DEFAULT_NUM_RFD;

	/* The RFDs are going to be put on lists later on, so initialize the
	 * lists now.
	 */
	INIT_LIST_HEAD(&rx_ring->recv_list);
	return 0;
}