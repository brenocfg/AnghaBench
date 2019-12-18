#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int instr_processed; } ;
struct octeon_instr_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  instr_pending; TYPE_3__ stats; int /*<<< orphan*/  host_write_index; int /*<<< orphan*/  octeon_read_index; int /*<<< orphan*/  fill_cnt; } ;
struct octeon_device_priv {int /*<<< orphan*/  droq_tasklet; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* soft_reset ) (struct octeon_device*) ;int /*<<< orphan*/  (* free_mbox ) (struct octeon_device*) ;int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_io_queues ) (struct octeon_device*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  work; } ;
struct TYPE_11__ {int /*<<< orphan*/  sriov_enabled; } ;
struct TYPE_15__ {int iq; int oq; } ;
struct octeon_device {int flags; size_t octeon_id; TYPE_6__* pci_dev; TYPE_4__ fn_list; int /*<<< orphan*/ * adapter_fw_state; TYPE_2__ nic_poll_work; TYPE_1__ sriov_info; TYPE_5__ io_qmask; int /*<<< orphan*/ * irq_name_storage; int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/  vector; struct octeon_device* ioq_vector; int /*<<< orphan*/  num_msix_irqs; int /*<<< orphan*/  msix_on; struct octeon_instr_queue** instr_queue; int /*<<< orphan*/  status; int /*<<< orphan*/  app_mode; scalar_t__ priv; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct handshake {int /*<<< orphan*/  started; int /*<<< orphan*/  started_ok; int /*<<< orphan*/  init; int /*<<< orphan*/  init_ok; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_16__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  CVM_DRV_INVALID_APP ; 
 int FW_IS_PRELOADED ; 
 int HZ ; 
 int LIO_FLAG_MSI_ENABLED ; 
 int MAX_OCTEON_DEVICES ; 
 int MAX_OCTEON_INSTR_QUEUES (struct octeon_device*) ; 
 int MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 int /*<<< orphan*/  OCTEON_CN23XX_PF (struct octeon_device*) ; 
 int /*<<< orphan*/  OCTEON_CN6XXX (struct octeon_device*) ; 
#define  OCT_DEV_BEGIN_STATE 144 
#define  OCT_DEV_CONSOLE_INIT_DONE 143 
#define  OCT_DEV_CORE_OK 142 
#define  OCT_DEV_DISPATCH_INIT_DONE 141 
#define  OCT_DEV_DROQ_INIT_DONE 140 
#define  OCT_DEV_HOST_OK 139 
#define  OCT_DEV_INSTR_QUEUE_INIT_DONE 138 
#define  OCT_DEV_INTR_SET_DONE 137 
#define  OCT_DEV_IN_RESET 136 
#define  OCT_DEV_IO_QUEUES_DONE 135 
#define  OCT_DEV_MBOX_SETUP_DONE 134 
#define  OCT_DEV_MSIX_ALLOC_VECTOR_DONE 133 
#define  OCT_DEV_PCI_ENABLE_DONE 132 
#define  OCT_DEV_PCI_MAP_DONE 131 
#define  OCT_DEV_RESP_LIST_INIT_DONE 130 
#define  OCT_DEV_RUNNING 129 
#define  OCT_DEV_SC_BUFF_POOL_INIT_DONE 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct octeon_device*) ; 
 struct handshake* handshake ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_get_state_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_process_iq_request_list (struct octeon_device*,struct octeon_instr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_process_ordered_list (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_wait_for_instr_fetch (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_wait_for_oq_pkts (struct octeon_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  octeon_delete_dispatch_list (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_delete_droq (struct octeon_device*,int) ; 
 int /*<<< orphan*/  octeon_delete_instr_queue (struct octeon_device*,int) ; 
 int /*<<< orphan*/  octeon_delete_response_list (struct octeon_device*) ; 
 int octeon_deregister_device (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_free_ioq_vector (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_free_sc_buffer_pool (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_free_sc_done_list (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_free_sc_zombie_list (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_pci_flr (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_remove_consoles (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_unmap_pci_barx (struct octeon_device*,int) ; 
 int /*<<< orphan*/  pci_clear_master (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_disable_sriov (TYPE_6__*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*) ; 
 int /*<<< orphan*/  stub2 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct octeon_device*) ; 
 int /*<<< orphan*/  stub4 (struct octeon_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_pending_requests (struct octeon_device*) ; 

__attribute__((used)) static void octeon_destroy_resources(struct octeon_device *oct)
{
	int i, refcount;
	struct msix_entry *msix_entries;
	struct octeon_device_priv *oct_priv =
		(struct octeon_device_priv *)oct->priv;

	struct handshake *hs;

	switch (atomic_read(&oct->status)) {
	case OCT_DEV_RUNNING:
	case OCT_DEV_CORE_OK:

		/* No more instructions will be forwarded. */
		atomic_set(&oct->status, OCT_DEV_IN_RESET);

		oct->app_mode = CVM_DRV_INVALID_APP;
		dev_dbg(&oct->pci_dev->dev, "Device state is now %s\n",
			lio_get_state_string(&oct->status));

		schedule_timeout_uninterruptible(HZ / 10);

		/* fallthrough */
	case OCT_DEV_HOST_OK:

		/* fallthrough */
	case OCT_DEV_CONSOLE_INIT_DONE:
		/* Remove any consoles */
		octeon_remove_consoles(oct);

		/* fallthrough */
	case OCT_DEV_IO_QUEUES_DONE:
		if (lio_wait_for_instr_fetch(oct))
			dev_err(&oct->pci_dev->dev, "IQ had pending instructions\n");

		if (wait_for_pending_requests(oct))
			dev_err(&oct->pci_dev->dev, "There were pending requests\n");

		/* Disable the input and output queues now. No more packets will
		 * arrive from Octeon, but we should wait for all packet
		 * processing to finish.
		 */
		oct->fn_list.disable_io_queues(oct);

		if (lio_wait_for_oq_pkts(oct))
			dev_err(&oct->pci_dev->dev, "OQ had pending packets\n");

		/* Force all requests waiting to be fetched by OCTEON to
		 * complete.
		 */
		for (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) {
			struct octeon_instr_queue *iq;

			if (!(oct->io_qmask.iq & BIT_ULL(i)))
				continue;
			iq = oct->instr_queue[i];

			if (atomic_read(&iq->instr_pending)) {
				spin_lock_bh(&iq->lock);
				iq->fill_cnt = 0;
				iq->octeon_read_index = iq->host_write_index;
				iq->stats.instr_processed +=
					atomic_read(&iq->instr_pending);
				lio_process_iq_request_list(oct, iq, 0);
				spin_unlock_bh(&iq->lock);
			}
		}

		lio_process_ordered_list(oct, 1);
		octeon_free_sc_done_list(oct);
		octeon_free_sc_zombie_list(oct);

	/* fallthrough */
	case OCT_DEV_INTR_SET_DONE:
		/* Disable interrupts  */
		oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

		if (oct->msix_on) {
			msix_entries = (struct msix_entry *)oct->msix_entries;
			for (i = 0; i < oct->num_msix_irqs - 1; i++) {
				if (oct->ioq_vector[i].vector) {
					/* clear the affinity_cpumask */
					irq_set_affinity_hint(
							msix_entries[i].vector,
							NULL);
					free_irq(msix_entries[i].vector,
						 &oct->ioq_vector[i]);
					oct->ioq_vector[i].vector = 0;
				}
			}
			/* non-iov vector's argument is oct struct */
			free_irq(msix_entries[i].vector, oct);

			pci_disable_msix(oct->pci_dev);
			kfree(oct->msix_entries);
			oct->msix_entries = NULL;
		} else {
			/* Release the interrupt line */
			free_irq(oct->pci_dev->irq, oct);

			if (oct->flags & LIO_FLAG_MSI_ENABLED)
				pci_disable_msi(oct->pci_dev);
		}

		kfree(oct->irq_name_storage);
		oct->irq_name_storage = NULL;

	/* fallthrough */
	case OCT_DEV_MSIX_ALLOC_VECTOR_DONE:
		if (OCTEON_CN23XX_PF(oct))
			octeon_free_ioq_vector(oct);

	/* fallthrough */
	case OCT_DEV_MBOX_SETUP_DONE:
		if (OCTEON_CN23XX_PF(oct))
			oct->fn_list.free_mbox(oct);

	/* fallthrough */
	case OCT_DEV_IN_RESET:
	case OCT_DEV_DROQ_INIT_DONE:
		/* Wait for any pending operations */
		mdelay(100);
		for (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) {
			if (!(oct->io_qmask.oq & BIT_ULL(i)))
				continue;
			octeon_delete_droq(oct, i);
		}

		/* Force any pending handshakes to complete */
		for (i = 0; i < MAX_OCTEON_DEVICES; i++) {
			hs = &handshake[i];

			if (hs->pci_dev) {
				handshake[oct->octeon_id].init_ok = 0;
				complete(&handshake[oct->octeon_id].init);
				handshake[oct->octeon_id].started_ok = 0;
				complete(&handshake[oct->octeon_id].started);
			}
		}

		/* fallthrough */
	case OCT_DEV_RESP_LIST_INIT_DONE:
		octeon_delete_response_list(oct);

		/* fallthrough */
	case OCT_DEV_INSTR_QUEUE_INIT_DONE:
		for (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) {
			if (!(oct->io_qmask.iq & BIT_ULL(i)))
				continue;
			octeon_delete_instr_queue(oct, i);
		}
#ifdef CONFIG_PCI_IOV
		if (oct->sriov_info.sriov_enabled)
			pci_disable_sriov(oct->pci_dev);
#endif
		/* fallthrough */
	case OCT_DEV_SC_BUFF_POOL_INIT_DONE:
		octeon_free_sc_buffer_pool(oct);

		/* fallthrough */
	case OCT_DEV_DISPATCH_INIT_DONE:
		octeon_delete_dispatch_list(oct);
		cancel_delayed_work_sync(&oct->nic_poll_work.work);

		/* fallthrough */
	case OCT_DEV_PCI_MAP_DONE:
		refcount = octeon_deregister_device(oct);

		/* Soft reset the octeon device before exiting.
		 * However, if fw was loaded from card (i.e. autoboot),
		 * perform an FLR instead.
		 * Implementation note: only soft-reset the device
		 * if it is a CN6XXX OR the LAST CN23XX device.
		 */
		if (atomic_read(oct->adapter_fw_state) == FW_IS_PRELOADED)
			octeon_pci_flr(oct);
		else if (OCTEON_CN6XXX(oct) || !refcount)
			oct->fn_list.soft_reset(oct);

		octeon_unmap_pci_barx(oct, 0);
		octeon_unmap_pci_barx(oct, 1);

		/* fallthrough */
	case OCT_DEV_PCI_ENABLE_DONE:
		pci_clear_master(oct->pci_dev);
		/* Disable the device, releasing the PCI INT */
		pci_disable_device(oct->pci_dev);

		/* fallthrough */
	case OCT_DEV_BEGIN_STATE:
		/* Nothing to be done here either */
		break;
	}                       /* end switch (oct->status) */

	tasklet_kill(&oct_priv->droq_tasklet);
}