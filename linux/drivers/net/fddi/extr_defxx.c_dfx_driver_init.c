#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int req_ttrt; int rcv_bufs_to_post; char* kmalloced; int kmalloced_dma; char* descr_block_virt; int descr_block_phys; char* cmd_req_virt; int cmd_req_phys; char* cmd_rsp_virt; int cmd_rsp_phys; char* rcv_block_virt; int rcv_block_phys; char* cons_block_virt; int cons_block_phys; struct device* bus_dev; int /*<<< orphan*/ * factory_mac_addr; int /*<<< orphan*/  burst_size; int /*<<< orphan*/  full_duplex_enb; } ;
typedef  char PI_DMA_CMD_RSP ;
typedef  char PI_DMA_CMD_REQ ;
typedef  char PI_DESCR_BLOCK ;
typedef  char PI_CONSUMER_BLOCK ;
typedef  TYPE_1__ DFX_board_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DBG_printk (char*,...) ; 
 int DFX_BUS_EISA (struct device*) ; 
 int DFX_BUS_TC (struct device*) ; 
 int DFX_K_FAILURE ; 
 scalar_t__ DFX_K_SUCCESS ; 
 scalar_t__ DFX_MMIO ; 
 int FDDI_K_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PI_ALIGN_K_DESC_BLK ; 
 int PI_CMD_REQ_K_SIZE_MAX ; 
 int PI_CMD_RSP_K_SIZE_MAX ; 
 int /*<<< orphan*/  PI_HOST_INT_K_DISABLE_ALL_INTS ; 
 int /*<<< orphan*/  PI_PCTRL_M_MLA ; 
 int /*<<< orphan*/  PI_PDATA_A_MLA_K_HI ; 
 int /*<<< orphan*/  PI_PDATA_A_MLA_K_LO ; 
 int /*<<< orphan*/  PI_PDATA_A_RESET_M_SKIP_ST ; 
 int /*<<< orphan*/  PI_PDATA_B_DMA_BURST_SIZE_DEF ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_HOST_INT_ENB ; 
 int PI_RCV_DATA_K_SIZE_MAX ; 
 int /*<<< orphan*/  PI_SNMP_K_FALSE ; 
 int RCV_BUFS_DEF ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dfx_bus_config_check (TYPE_1__*) ; 
 int /*<<< orphan*/  dfx_bus_init (struct net_device*) ; 
 int /*<<< orphan*/  dfx_hw_dma_uninit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dfx_hw_port_ctrl_req (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,char*,char*,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char const*) ; 

__attribute__((used)) static int dfx_driver_init(struct net_device *dev, const char *print_name,
			   resource_size_t bar_start)
{
	DFX_board_t *bp = netdev_priv(dev);
	struct device *bdev = bp->bus_dev;
	int dfx_bus_pci = dev_is_pci(bdev);
	int dfx_bus_eisa = DFX_BUS_EISA(bdev);
	int dfx_bus_tc = DFX_BUS_TC(bdev);
	int dfx_use_mmio = DFX_MMIO || dfx_bus_tc;
	int alloc_size;			/* total buffer size needed */
	char *top_v, *curr_v;		/* virtual addrs into memory block */
	dma_addr_t top_p, curr_p;	/* physical addrs into memory block */
	u32 data;			/* host data register value */
	__le32 le32;
	char *board_name = NULL;

	DBG_printk("In dfx_driver_init...\n");

	/* Initialize bus-specific hardware registers */

	dfx_bus_init(dev);

	/*
	 * Initialize default values for configurable parameters
	 *
	 * Note: All of these parameters are ones that a user may
	 *       want to customize.  It'd be nice to break these
	 *		 out into Space.c or someplace else that's more
	 *		 accessible/understandable than this file.
	 */

	bp->full_duplex_enb		= PI_SNMP_K_FALSE;
	bp->req_ttrt			= 8 * 12500;		/* 8ms in 80 nanosec units */
	bp->burst_size			= PI_PDATA_B_DMA_BURST_SIZE_DEF;
	bp->rcv_bufs_to_post	= RCV_BUFS_DEF;

	/*
	 * Ensure that HW configuration is OK
	 *
	 * Note: Depending on the hardware revision, we may need to modify
	 *       some of the configurable parameters to workaround hardware
	 *       limitations.  We'll perform this configuration check AFTER
	 *       setting the parameters to their default values.
	 */

	dfx_bus_config_check(bp);

	/* Disable PDQ interrupts first */

	dfx_port_write_long(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);

	/* Place adapter in DMA_UNAVAILABLE state by resetting adapter */

	(void) dfx_hw_dma_uninit(bp, PI_PDATA_A_RESET_M_SKIP_ST);

	/*  Read the factory MAC address from the adapter then save it */

	if (dfx_hw_port_ctrl_req(bp, PI_PCTRL_M_MLA, PI_PDATA_A_MLA_K_LO, 0,
				 &data) != DFX_K_SUCCESS) {
		printk("%s: Could not read adapter factory MAC address!\n",
		       print_name);
		return DFX_K_FAILURE;
	}
	le32 = cpu_to_le32(data);
	memcpy(&bp->factory_mac_addr[0], &le32, sizeof(u32));

	if (dfx_hw_port_ctrl_req(bp, PI_PCTRL_M_MLA, PI_PDATA_A_MLA_K_HI, 0,
				 &data) != DFX_K_SUCCESS) {
		printk("%s: Could not read adapter factory MAC address!\n",
		       print_name);
		return DFX_K_FAILURE;
	}
	le32 = cpu_to_le32(data);
	memcpy(&bp->factory_mac_addr[4], &le32, sizeof(u16));

	/*
	 * Set current address to factory address
	 *
	 * Note: Node address override support is handled through
	 *       dfx_ctl_set_mac_address.
	 */

	memcpy(dev->dev_addr, bp->factory_mac_addr, FDDI_K_ALEN);
	if (dfx_bus_tc)
		board_name = "DEFTA";
	if (dfx_bus_eisa)
		board_name = "DEFEA";
	if (dfx_bus_pci)
		board_name = "DEFPA";
	pr_info("%s: %s at %s addr = 0x%llx, IRQ = %d, Hardware addr = %pMF\n",
		print_name, board_name, dfx_use_mmio ? "MMIO" : "I/O",
		(long long)bar_start, dev->irq, dev->dev_addr);

	/*
	 * Get memory for descriptor block, consumer block, and other buffers
	 * that need to be DMA read or written to by the adapter.
	 */

	alloc_size = sizeof(PI_DESCR_BLOCK) +
					PI_CMD_REQ_K_SIZE_MAX +
					PI_CMD_RSP_K_SIZE_MAX +
#ifndef DYNAMIC_BUFFERS
					(bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX) +
#endif
					sizeof(PI_CONSUMER_BLOCK) +
					(PI_ALIGN_K_DESC_BLK - 1);
	bp->kmalloced = top_v = dma_alloc_coherent(bp->bus_dev, alloc_size,
						   &bp->kmalloced_dma,
						   GFP_ATOMIC);
	if (top_v == NULL)
		return DFX_K_FAILURE;

	top_p = bp->kmalloced_dma;	/* get physical address of buffer */

	/*
	 *  To guarantee the 8K alignment required for the descriptor block, 8K - 1
	 *  plus the amount of memory needed was allocated.  The physical address
	 *	is now 8K aligned.  By carving up the memory in a specific order,
	 *  we'll guarantee the alignment requirements for all other structures.
	 *
	 *  Note: If the assumptions change regarding the non-paged, non-cached,
	 *		  physically contiguous nature of the memory block or the address
	 *		  alignments, then we'll need to implement a different algorithm
	 *		  for allocating the needed memory.
	 */

	curr_p = ALIGN(top_p, PI_ALIGN_K_DESC_BLK);
	curr_v = top_v + (curr_p - top_p);

	/* Reserve space for descriptor block */

	bp->descr_block_virt = (PI_DESCR_BLOCK *) curr_v;
	bp->descr_block_phys = curr_p;
	curr_v += sizeof(PI_DESCR_BLOCK);
	curr_p += sizeof(PI_DESCR_BLOCK);

	/* Reserve space for command request buffer */

	bp->cmd_req_virt = (PI_DMA_CMD_REQ *) curr_v;
	bp->cmd_req_phys = curr_p;
	curr_v += PI_CMD_REQ_K_SIZE_MAX;
	curr_p += PI_CMD_REQ_K_SIZE_MAX;

	/* Reserve space for command response buffer */

	bp->cmd_rsp_virt = (PI_DMA_CMD_RSP *) curr_v;
	bp->cmd_rsp_phys = curr_p;
	curr_v += PI_CMD_RSP_K_SIZE_MAX;
	curr_p += PI_CMD_RSP_K_SIZE_MAX;

	/* Reserve space for the LLC host receive queue buffers */

	bp->rcv_block_virt = curr_v;
	bp->rcv_block_phys = curr_p;

#ifndef DYNAMIC_BUFFERS
	curr_v += (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX);
	curr_p += (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX);
#endif

	/* Reserve space for the consumer block */

	bp->cons_block_virt = (PI_CONSUMER_BLOCK *) curr_v;
	bp->cons_block_phys = curr_p;

	/* Display virtual and physical addresses if debug driver */

	DBG_printk("%s: Descriptor block virt = %p, phys = %pad\n",
		   print_name, bp->descr_block_virt, &bp->descr_block_phys);
	DBG_printk("%s: Command Request buffer virt = %p, phys = %pad\n",
		   print_name, bp->cmd_req_virt, &bp->cmd_req_phys);
	DBG_printk("%s: Command Response buffer virt = %p, phys = %pad\n",
		   print_name, bp->cmd_rsp_virt, &bp->cmd_rsp_phys);
	DBG_printk("%s: Receive buffer block virt = %p, phys = %pad\n",
		   print_name, bp->rcv_block_virt, &bp->rcv_block_phys);
	DBG_printk("%s: Consumer block virt = %p, phys = %pad\n",
		   print_name, bp->cons_block_virt, &bp->cons_block_phys);

	return DFX_K_SUCCESS;
}