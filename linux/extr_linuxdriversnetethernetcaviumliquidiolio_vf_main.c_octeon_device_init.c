#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ (* enable_io_queues ) (struct octeon_device*) ;int /*<<< orphan*/  (* enable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;scalar_t__ (* setup_mbox ) (struct octeon_device*) ;scalar_t__ (* setup_device_regs ) (struct octeon_device*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  rings_per_vf; } ;
struct octeon_device {int rev_id; int num_oqs; int /*<<< orphan*/  status; TYPE_3__** droq; TYPE_4__* pci_dev; TYPE_2__ fn_list; TYPE_1__ sriov_info; int /*<<< orphan*/  app_mode; int /*<<< orphan*/  chip_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  pkts_credit_reg; int /*<<< orphan*/  max_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_DRV_NIC_APP ; 
 int /*<<< orphan*/  LIQUIDIO_VERSION ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 int /*<<< orphan*/  OCTEON_CN23XX_VF_VID ; 
 int /*<<< orphan*/  OCT_DEV_BEGIN_STATE ; 
 int /*<<< orphan*/  OCT_DEV_CORE_OK ; 
 int /*<<< orphan*/  OCT_DEV_DISPATCH_INIT_DONE ; 
 int /*<<< orphan*/  OCT_DEV_DROQ_INIT_DONE ; 
 int /*<<< orphan*/  OCT_DEV_HOST_OK ; 
 int /*<<< orphan*/  OCT_DEV_INSTR_QUEUE_INIT_DONE ; 
 int /*<<< orphan*/  OCT_DEV_INTR_SET_DONE ; 
 int /*<<< orphan*/  OCT_DEV_IO_QUEUES_DONE ; 
 int /*<<< orphan*/  OCT_DEV_MBOX_SETUP_DONE ; 
 int /*<<< orphan*/  OCT_DEV_MSIX_ALLOC_VECTOR_DONE ; 
 int /*<<< orphan*/  OCT_DEV_PCI_ENABLE_DONE ; 
 int /*<<< orphan*/  OCT_DEV_PCI_MAP_DONE ; 
 int /*<<< orphan*/  OCT_DEV_RESP_LIST_INIT_DONE ; 
 int /*<<< orphan*/  OCT_DEV_RUNNING ; 
 int /*<<< orphan*/  OCT_DEV_SC_BUFF_POOL_INIT_DONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cn23xx_octeon_pfvf_handshake (struct octeon_device*) ; 
 scalar_t__ cn23xx_setup_octeon_vf_device (struct octeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ liquidio_init_nic_module (struct octeon_device*) ; 
 scalar_t__ octeon_allocate_ioq_vector (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_init_dispatch_list (struct octeon_device*) ; 
 scalar_t__ octeon_pci_os_setup (struct octeon_device*) ; 
 scalar_t__ octeon_set_io_queues_off (struct octeon_device*) ; 
 scalar_t__ octeon_setup_instr_queues (struct octeon_device*) ; 
 scalar_t__ octeon_setup_interrupt (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_setup_output_queues (struct octeon_device*) ; 
 scalar_t__ octeon_setup_response_list (struct octeon_device*) ; 
 scalar_t__ octeon_setup_sc_buffer_pool (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_4__*,int,int*) ; 
 scalar_t__ stub1 (struct octeon_device*) ; 
 scalar_t__ stub2 (struct octeon_device*) ; 
 int /*<<< orphan*/  stub3 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct octeon_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_device_init(struct octeon_device *oct)
{
	u32 rev_id;
	int j;

	atomic_set(&oct->status, OCT_DEV_BEGIN_STATE);

	/* Enable access to the octeon device and make its DMA capability
	 * known to the OS.
	 */
	if (octeon_pci_os_setup(oct))
		return 1;
	atomic_set(&oct->status, OCT_DEV_PCI_ENABLE_DONE);

	oct->chip_id = OCTEON_CN23XX_VF_VID;
	pci_read_config_dword(oct->pci_dev, 8, &rev_id);
	oct->rev_id = rev_id & 0xff;

	if (cn23xx_setup_octeon_vf_device(oct))
		return 1;

	atomic_set(&oct->status, OCT_DEV_PCI_MAP_DONE);

	oct->app_mode = CVM_DRV_NIC_APP;

	/* Initialize the dispatch mechanism used to push packets arriving on
	 * Octeon Output queues.
	 */
	if (octeon_init_dispatch_list(oct))
		return 1;

	atomic_set(&oct->status, OCT_DEV_DISPATCH_INIT_DONE);

	if (octeon_set_io_queues_off(oct)) {
		dev_err(&oct->pci_dev->dev, "setting io queues off failed\n");
		return 1;
	}

	if (oct->fn_list.setup_device_regs(oct)) {
		dev_err(&oct->pci_dev->dev, "device registers configuration failed\n");
		return 1;
	}

	/* Initialize soft command buffer pool */
	if (octeon_setup_sc_buffer_pool(oct)) {
		dev_err(&oct->pci_dev->dev, "sc buffer pool allocation failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_SC_BUFF_POOL_INIT_DONE);

	/* Setup the data structures that manage this Octeon's Input queues. */
	if (octeon_setup_instr_queues(oct)) {
		dev_err(&oct->pci_dev->dev, "instruction queue initialization failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_INSTR_QUEUE_INIT_DONE);

	/* Initialize lists to manage the requests of different types that
	 * arrive from user & kernel applications for this octeon device.
	 */
	if (octeon_setup_response_list(oct)) {
		dev_err(&oct->pci_dev->dev, "Response list allocation failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_RESP_LIST_INIT_DONE);

	if (octeon_setup_output_queues(oct)) {
		dev_err(&oct->pci_dev->dev, "Output queue initialization failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_DROQ_INIT_DONE);

	if (oct->fn_list.setup_mbox(oct)) {
		dev_err(&oct->pci_dev->dev, "Mailbox setup failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_MBOX_SETUP_DONE);

	if (octeon_allocate_ioq_vector(oct, oct->sriov_info.rings_per_vf)) {
		dev_err(&oct->pci_dev->dev, "ioq vector allocation failed\n");
		return 1;
	}
	atomic_set(&oct->status, OCT_DEV_MSIX_ALLOC_VECTOR_DONE);

	dev_info(&oct->pci_dev->dev, "OCTEON_CN23XX VF Version: %s, %d ioqs\n",
		 LIQUIDIO_VERSION, oct->sriov_info.rings_per_vf);

	/* Setup the interrupt handler and record the INT SUM register address*/
	if (octeon_setup_interrupt(oct, oct->sriov_info.rings_per_vf))
		return 1;

	atomic_set(&oct->status, OCT_DEV_INTR_SET_DONE);

	/* ***************************************************************
	 * The interrupts need to be enabled for the PF<-->VF handshake.
	 * They are [re]-enabled after the PF<-->VF handshake so that the
	 * correct OQ tick value is used (i.e. the value retrieved from
	 * the PF as part of the handshake).
	 */

	/* Enable Octeon device interrupts */
	oct->fn_list.enable_interrupt(oct, OCTEON_ALL_INTR);

	if (cn23xx_octeon_pfvf_handshake(oct))
		return 1;

	/* Here we [re]-enable the interrupts so that the correct OQ tick value
	 * is used (i.e. the value that was retrieved during the handshake)
	 */

	/* Enable Octeon device interrupts */
	oct->fn_list.enable_interrupt(oct, OCTEON_ALL_INTR);
	/* *************************************************************** */

	/* Enable the input and output queues for this Octeon device */
	if (oct->fn_list.enable_io_queues(oct)) {
		dev_err(&oct->pci_dev->dev, "enabling io queues failed\n");
		return 1;
	}

	atomic_set(&oct->status, OCT_DEV_IO_QUEUES_DONE);

	atomic_set(&oct->status, OCT_DEV_HOST_OK);

	/* Send Credit for Octeon Output queues. Credits are always sent after
	 * the output queue is enabled.
	 */
	for (j = 0; j < oct->num_oqs; j++)
		writel(oct->droq[j]->max_count, oct->droq[j]->pkts_credit_reg);

	/* Packets can start arriving on the output queues from this point. */

	atomic_set(&oct->status, OCT_DEV_CORE_OK);

	atomic_set(&oct->status, OCT_DEV_RUNNING);

	if (liquidio_init_nic_module(oct))
		return 1;

	return 0;
}