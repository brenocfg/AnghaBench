#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
typedef  int ulong ;
struct pci_dev {scalar_t__ device; } ;
struct TYPE_25__ {int max_host_qng; int /*<<< orphan*/  serial_number_word3; int /*<<< orphan*/  serial_number_word2; int /*<<< orphan*/  serial_number_word1; int /*<<< orphan*/  scsi_reset_delay; int /*<<< orphan*/  start_motor; int /*<<< orphan*/  tagqng_able; int /*<<< orphan*/  sdtr_speed4; int /*<<< orphan*/  sdtr_speed3; int /*<<< orphan*/  sdtr_speed2; int /*<<< orphan*/  sdtr_speed1; int /*<<< orphan*/  wdtr_able; int /*<<< orphan*/  bios_ctrl; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  termination_lvd; int /*<<< orphan*/  max_dvc_qng; int /*<<< orphan*/  adapter_scsi_id; } ;
struct TYPE_15__ {int max_host_qng; int /*<<< orphan*/  serial_number_word3; int /*<<< orphan*/  serial_number_word2; int /*<<< orphan*/  serial_number_word1; int /*<<< orphan*/  scsi_reset_delay; int /*<<< orphan*/  start_motor; int /*<<< orphan*/  tagqng_able; int /*<<< orphan*/  sdtr_speed4; int /*<<< orphan*/  sdtr_speed3; int /*<<< orphan*/  sdtr_speed2; int /*<<< orphan*/  sdtr_speed1; int /*<<< orphan*/  wdtr_able; int /*<<< orphan*/  bios_ctrl; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  termination_lvd; int /*<<< orphan*/  max_dvc_qng; int /*<<< orphan*/  adapter_scsi_id; } ;
struct TYPE_16__ {int max_host_qng; int /*<<< orphan*/  serial_number_word3; int /*<<< orphan*/  serial_number_word2; int /*<<< orphan*/  serial_number_word1; int /*<<< orphan*/  scsi_reset_delay; int /*<<< orphan*/  start_motor; int /*<<< orphan*/  tagqng_able; int /*<<< orphan*/  ultra_able; int /*<<< orphan*/  sdtr_able; int /*<<< orphan*/  wdtr_able; int /*<<< orphan*/  bios_ctrl; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  termination; int /*<<< orphan*/  max_dvc_qng; int /*<<< orphan*/  adapter_scsi_id; } ;
struct TYPE_23__ {int max_total_qng; int /*<<< orphan*/ * adapter_info; int /*<<< orphan*/  max_tag_qng; int /*<<< orphan*/  no_scam; int /*<<< orphan*/  cntl; int /*<<< orphan*/  start_motor; int /*<<< orphan*/  use_cmd_qng; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  init_sdtr; } ;
struct TYPE_19__ {TYPE_9__ adv_38C1600_eep; TYPE_10__ adv_38C0800_eep; TYPE_11__ adv_3550_eep; TYPE_7__ asc_eep; } ;
struct TYPE_20__ {int /*<<< orphan*/  serial3; int /*<<< orphan*/  serial2; int /*<<< orphan*/  serial1; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  termination; } ;
struct TYPE_21__ {int /*<<< orphan*/  isa_dma_channel; int /*<<< orphan*/  chip_scsi_id; int /*<<< orphan*/ * adapter_info; int /*<<< orphan*/ * max_tag_qng; int /*<<< orphan*/  isa_dma_speed; int /*<<< orphan*/  cmd_qng_enabled; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/  sdtr_enable; } ;
struct TYPE_18__ {TYPE_4__ adv_dvc_cfg; TYPE_5__ asc_dvc_cfg; } ;
struct TYPE_24__ {scalar_t__ chip_type; int max_host_qng; scalar_t__ iop_base; int /*<<< orphan*/  chip_scsi_id; TYPE_4__* cfg; int /*<<< orphan*/  scsi_reset_wait; int /*<<< orphan*/  start_motor; int /*<<< orphan*/  tagqng_able; int /*<<< orphan*/  sdtr_speed4; int /*<<< orphan*/  sdtr_speed3; int /*<<< orphan*/  sdtr_speed2; int /*<<< orphan*/  sdtr_speed1; int /*<<< orphan*/  wdtr_able; int /*<<< orphan*/  bios_ctrl; int /*<<< orphan*/  max_dvc_qng; int /*<<< orphan*/  ultra_able; int /*<<< orphan*/  sdtr_able; struct asc_board* drv_ptr; } ;
struct TYPE_22__ {int bus_type; unsigned int iop_base; int max_total_qng; int /*<<< orphan*/  overrun_buf; int /*<<< orphan*/  overrun_dma; scalar_t__ err_code; int /*<<< orphan*/  init_state; TYPE_5__* cfg; int /*<<< orphan*/  no_scam; int /*<<< orphan*/  dvc_cntl; int /*<<< orphan*/  start_motor; struct asc_board* drv_ptr; } ;
struct TYPE_17__ {TYPE_8__ adv_dvc_var; TYPE_6__ asc_dvc_var; } ;
struct asc_board {unsigned int ioport; int bios_signature; int bios_version; int bios_codeseg; int bios_codelen; scalar_t__ ioremap_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  asc_n_io_port; int /*<<< orphan*/  init_tidmask; TYPE_3__ eep_config; TYPE_2__ dvc_cfg; TYPE_1__ dvc_var; } ;
struct Scsi_Host {int unchecked_isa_dma; unsigned int io_port; int can_queue; int sg_tablesize; int base; int /*<<< orphan*/  dma_channel; int /*<<< orphan*/  this_id; int /*<<< orphan*/  max_cmd_len; scalar_t__ max_lun; scalar_t__ max_id; scalar_t__ max_channel; } ;
typedef  scalar_t__ AdvPortAddr ;
typedef  TYPE_6__ ASC_DVC_VAR ;
typedef  TYPE_7__ ASCEEP_CONFIG ;
typedef  TYPE_8__ ADV_DVC_VAR ;
typedef  TYPE_9__ ADVEEP_38C1600_CONFIG ;
typedef  TYPE_10__ ADVEEP_38C0800_CONFIG ;
typedef  TYPE_11__ ADVEEP_3550_CONFIG ;

/* Variables and functions */
 scalar_t__ ADV_CHIP_ASC3550 ; 
 scalar_t__ ADV_CHIP_ASC38C0800 ; 
 scalar_t__ ADV_CHIP_ASC38C1600 ; 
 int /*<<< orphan*/  ADV_MAX_CDB_LEN ; 
 scalar_t__ ADV_MAX_LUN ; 
 int ADV_MAX_SG_LIST ; 
 scalar_t__ ADV_MAX_TID ; 
 int /*<<< orphan*/  ADV_TID_TO_TIDMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASC_DBG (int,char*,...) ; 
 int /*<<< orphan*/  ASC_DBG_PRT_SCSI_HOST (int,struct Scsi_Host*) ; 
 int /*<<< orphan*/  ASC_EEP_SET_CHIP_ID (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASC_EEP_SET_DMA_SPD (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASC_IOADR_GAP ; 
#define  ASC_IS_EISA 131 
#define  ASC_IS_ISA 130 
#define  ASC_IS_PCI 129 
#define  ASC_IS_VL 128 
 int /*<<< orphan*/  ASC_MAX_CDB_LEN ; 
 scalar_t__ ASC_MAX_LUN ; 
 scalar_t__ ASC_MAX_TID ; 
 scalar_t__ ASC_NARROW_BOARD (struct asc_board*) ; 
 int /*<<< orphan*/  ASC_OVERRUN_BSIZE ; 
 int ASC_SG_LIST_PER_Q ; 
 scalar_t__ AdvInitGetConfig (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  AdvReadWordLram (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscEnableIsaDma (int /*<<< orphan*/ ) ; 
 int AscGetChipBiosAddress (unsigned int,int) ; 
 int AscInitAsc1000Driver (TYPE_6__*) ; 
 scalar_t__ AscInitGetConfig (struct Scsi_Host*) ; 
 scalar_t__ AscInitSetConfig (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  BIOS_CODELEN ; 
 int /*<<< orphan*/  BIOS_CODESEG ; 
 int /*<<< orphan*/  BIOS_SIGNATURE ; 
 int /*<<< orphan*/  BIOS_VERSION ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NO_ISA_DMA ; 
 scalar_t__ PCI_DEVICE_ID_38C0800_REV1 ; 
 scalar_t__ PCI_DEVICE_ID_ASP_ABP940UW ; 
 int SG_ALL ; 
 int /*<<< orphan*/  advansys_interrupt ; 
 int /*<<< orphan*/  advansys_wide_free_mem (struct asc_board*) ; 
 scalar_t__ advansys_wide_init_chip (struct Scsi_Host*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 scalar_t__ inp (unsigned int) ; 
 scalar_t__ inpw (unsigned int) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_ioremap_bar (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int request_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,long,...) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advansys_board_found(struct Scsi_Host *shost, unsigned int iop,
				int bus_type)
{
	struct pci_dev *pdev;
	struct asc_board *boardp = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc_varp = NULL;
	ADV_DVC_VAR *adv_dvc_varp = NULL;
	int share_irq, warn_code, ret;

	pdev = (bus_type == ASC_IS_PCI) ? to_pci_dev(boardp->dev) : NULL;

	if (ASC_NARROW_BOARD(boardp)) {
		ASC_DBG(1, "narrow board\n");
		asc_dvc_varp = &boardp->dvc_var.asc_dvc_var;
		asc_dvc_varp->bus_type = bus_type;
		asc_dvc_varp->drv_ptr = boardp;
		asc_dvc_varp->cfg = &boardp->dvc_cfg.asc_dvc_cfg;
		asc_dvc_varp->iop_base = iop;
	} else {
#ifdef CONFIG_PCI
		adv_dvc_varp = &boardp->dvc_var.adv_dvc_var;
		adv_dvc_varp->drv_ptr = boardp;
		adv_dvc_varp->cfg = &boardp->dvc_cfg.adv_dvc_cfg;
		if (pdev->device == PCI_DEVICE_ID_ASP_ABP940UW) {
			ASC_DBG(1, "wide board ASC-3550\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC3550;
		} else if (pdev->device == PCI_DEVICE_ID_38C0800_REV1) {
			ASC_DBG(1, "wide board ASC-38C0800\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC38C0800;
		} else {
			ASC_DBG(1, "wide board ASC-38C1600\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC38C1600;
		}

		boardp->asc_n_io_port = pci_resource_len(pdev, 1);
		boardp->ioremap_addr = pci_ioremap_bar(pdev, 1);
		if (!boardp->ioremap_addr) {
			shost_printk(KERN_ERR, shost, "ioremap(%lx, %d) "
					"returned NULL\n",
					(long)pci_resource_start(pdev, 1),
					boardp->asc_n_io_port);
			ret = -ENODEV;
			goto err_shost;
		}
		adv_dvc_varp->iop_base = (AdvPortAddr)boardp->ioremap_addr;
		ASC_DBG(1, "iop_base: 0x%p\n", adv_dvc_varp->iop_base);

		/*
		 * Even though it isn't used to access wide boards, other
		 * than for the debug line below, save I/O Port address so
		 * that it can be reported.
		 */
		boardp->ioport = iop;

		ASC_DBG(1, "iopb_chip_id_1 0x%x, iopw_chip_id_0 0x%x\n",
				(ushort)inp(iop + 1), (ushort)inpw(iop));
#endif /* CONFIG_PCI */
	}

	if (ASC_NARROW_BOARD(boardp)) {
		/*
		 * Set the board bus type and PCI IRQ before
		 * calling AscInitGetConfig().
		 */
		switch (asc_dvc_varp->bus_type) {
#ifdef CONFIG_ISA
		case ASC_IS_ISA:
			shost->unchecked_isa_dma = true;
			share_irq = 0;
			break;
		case ASC_IS_VL:
			shost->unchecked_isa_dma = false;
			share_irq = 0;
			break;
		case ASC_IS_EISA:
			shost->unchecked_isa_dma = false;
			share_irq = IRQF_SHARED;
			break;
#endif /* CONFIG_ISA */
#ifdef CONFIG_PCI
		case ASC_IS_PCI:
			shost->unchecked_isa_dma = false;
			share_irq = IRQF_SHARED;
			break;
#endif /* CONFIG_PCI */
		default:
			shost_printk(KERN_ERR, shost, "unknown adapter type: "
					"%d\n", asc_dvc_varp->bus_type);
			shost->unchecked_isa_dma = false;
			share_irq = 0;
			break;
		}

		/*
		 * NOTE: AscInitGetConfig() may change the board's
		 * bus_type value. The bus_type value should no
		 * longer be used. If the bus_type field must be
		 * referenced only use the bit-wise AND operator "&".
		 */
		ASC_DBG(2, "AscInitGetConfig()\n");
		ret = AscInitGetConfig(shost) ? -ENODEV : 0;
	} else {
#ifdef CONFIG_PCI
		/*
		 * For Wide boards set PCI information before calling
		 * AdvInitGetConfig().
		 */
		shost->unchecked_isa_dma = false;
		share_irq = IRQF_SHARED;
		ASC_DBG(2, "AdvInitGetConfig()\n");

		ret = AdvInitGetConfig(pdev, shost) ? -ENODEV : 0;
#else
		share_irq = 0;
		ret = -ENODEV;
#endif /* CONFIG_PCI */
	}

	if (ret)
		goto err_unmap;

	/*
	 * Save the EEPROM configuration so that it can be displayed
	 * from /proc/scsi/advansys/[0...].
	 */
	if (ASC_NARROW_BOARD(boardp)) {

		ASCEEP_CONFIG *ep;

		/*
		 * Set the adapter's target id bit in the 'init_tidmask' field.
		 */
		boardp->init_tidmask |=
		    ADV_TID_TO_TIDMASK(asc_dvc_varp->cfg->chip_scsi_id);

		/*
		 * Save EEPROM settings for the board.
		 */
		ep = &boardp->eep_config.asc_eep;

		ep->init_sdtr = asc_dvc_varp->cfg->sdtr_enable;
		ep->disc_enable = asc_dvc_varp->cfg->disc_enable;
		ep->use_cmd_qng = asc_dvc_varp->cfg->cmd_qng_enabled;
		ASC_EEP_SET_DMA_SPD(ep, asc_dvc_varp->cfg->isa_dma_speed);
		ep->start_motor = asc_dvc_varp->start_motor;
		ep->cntl = asc_dvc_varp->dvc_cntl;
		ep->no_scam = asc_dvc_varp->no_scam;
		ep->max_total_qng = asc_dvc_varp->max_total_qng;
		ASC_EEP_SET_CHIP_ID(ep, asc_dvc_varp->cfg->chip_scsi_id);
		/* 'max_tag_qng' is set to the same value for every device. */
		ep->max_tag_qng = asc_dvc_varp->cfg->max_tag_qng[0];
		ep->adapter_info[0] = asc_dvc_varp->cfg->adapter_info[0];
		ep->adapter_info[1] = asc_dvc_varp->cfg->adapter_info[1];
		ep->adapter_info[2] = asc_dvc_varp->cfg->adapter_info[2];
		ep->adapter_info[3] = asc_dvc_varp->cfg->adapter_info[3];
		ep->adapter_info[4] = asc_dvc_varp->cfg->adapter_info[4];
		ep->adapter_info[5] = asc_dvc_varp->cfg->adapter_info[5];

		/*
		 * Modify board configuration.
		 */
		ASC_DBG(2, "AscInitSetConfig()\n");
		ret = AscInitSetConfig(pdev, shost) ? -ENODEV : 0;
		if (ret)
			goto err_unmap;
	} else {
		ADVEEP_3550_CONFIG *ep_3550;
		ADVEEP_38C0800_CONFIG *ep_38C0800;
		ADVEEP_38C1600_CONFIG *ep_38C1600;

		/*
		 * Save Wide EEP Configuration Information.
		 */
		if (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) {
			ep_3550 = &boardp->eep_config.adv_3550_eep;

			ep_3550->adapter_scsi_id = adv_dvc_varp->chip_scsi_id;
			ep_3550->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_3550->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_3550->termination = adv_dvc_varp->cfg->termination;
			ep_3550->disc_enable = adv_dvc_varp->cfg->disc_enable;
			ep_3550->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_3550->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_3550->sdtr_able = adv_dvc_varp->sdtr_able;
			ep_3550->ultra_able = adv_dvc_varp->ultra_able;
			ep_3550->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_3550->start_motor = adv_dvc_varp->start_motor;
			ep_3550->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_wait;
			ep_3550->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_3550->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_3550->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		} else if (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) {
			ep_38C0800 = &boardp->eep_config.adv_38C0800_eep;

			ep_38C0800->adapter_scsi_id =
			    adv_dvc_varp->chip_scsi_id;
			ep_38C0800->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_38C0800->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_38C0800->termination_lvd =
			    adv_dvc_varp->cfg->termination;
			ep_38C0800->disc_enable =
			    adv_dvc_varp->cfg->disc_enable;
			ep_38C0800->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_38C0800->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_38C0800->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C0800->sdtr_speed1 = adv_dvc_varp->sdtr_speed1;
			ep_38C0800->sdtr_speed2 = adv_dvc_varp->sdtr_speed2;
			ep_38C0800->sdtr_speed3 = adv_dvc_varp->sdtr_speed3;
			ep_38C0800->sdtr_speed4 = adv_dvc_varp->sdtr_speed4;
			ep_38C0800->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C0800->start_motor = adv_dvc_varp->start_motor;
			ep_38C0800->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_wait;
			ep_38C0800->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_38C0800->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_38C0800->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		} else {
			ep_38C1600 = &boardp->eep_config.adv_38C1600_eep;

			ep_38C1600->adapter_scsi_id =
			    adv_dvc_varp->chip_scsi_id;
			ep_38C1600->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_38C1600->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_38C1600->termination_lvd =
			    adv_dvc_varp->cfg->termination;
			ep_38C1600->disc_enable =
			    adv_dvc_varp->cfg->disc_enable;
			ep_38C1600->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_38C1600->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_38C1600->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C1600->sdtr_speed1 = adv_dvc_varp->sdtr_speed1;
			ep_38C1600->sdtr_speed2 = adv_dvc_varp->sdtr_speed2;
			ep_38C1600->sdtr_speed3 = adv_dvc_varp->sdtr_speed3;
			ep_38C1600->sdtr_speed4 = adv_dvc_varp->sdtr_speed4;
			ep_38C1600->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C1600->start_motor = adv_dvc_varp->start_motor;
			ep_38C1600->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_wait;
			ep_38C1600->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_38C1600->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_38C1600->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		}

		/*
		 * Set the adapter's target id bit in the 'init_tidmask' field.
		 */
		boardp->init_tidmask |=
		    ADV_TID_TO_TIDMASK(adv_dvc_varp->chip_scsi_id);
	}

	/*
	 * Channels are numbered beginning with 0. For AdvanSys one host
	 * structure supports one channel. Multi-channel boards have a
	 * separate host structure for each channel.
	 */
	shost->max_channel = 0;
	if (ASC_NARROW_BOARD(boardp)) {
		shost->max_id = ASC_MAX_TID + 1;
		shost->max_lun = ASC_MAX_LUN + 1;
		shost->max_cmd_len = ASC_MAX_CDB_LEN;

		shost->io_port = asc_dvc_varp->iop_base;
		boardp->asc_n_io_port = ASC_IOADR_GAP;
		shost->this_id = asc_dvc_varp->cfg->chip_scsi_id;

		/* Set maximum number of queues the adapter can handle. */
		shost->can_queue = asc_dvc_varp->max_total_qng;
	} else {
		shost->max_id = ADV_MAX_TID + 1;
		shost->max_lun = ADV_MAX_LUN + 1;
		shost->max_cmd_len = ADV_MAX_CDB_LEN;

		/*
		 * Save the I/O Port address and length even though
		 * I/O ports are not used to access Wide boards.
		 * Instead the Wide boards are accessed with
		 * PCI Memory Mapped I/O.
		 */
		shost->io_port = iop;

		shost->this_id = adv_dvc_varp->chip_scsi_id;

		/* Set maximum number of queues the adapter can handle. */
		shost->can_queue = adv_dvc_varp->max_host_qng;
	}

	/*
	 * Set the maximum number of scatter-gather elements the
	 * adapter can handle.
	 */
	if (ASC_NARROW_BOARD(boardp)) {
		/*
		 * Allow two commands with 'sg_tablesize' scatter-gather
		 * elements to be executed simultaneously. This value is
		 * the theoretical hardware limit. It may be decreased
		 * below.
		 */
		shost->sg_tablesize =
		    (((asc_dvc_varp->max_total_qng - 2) / 2) *
		     ASC_SG_LIST_PER_Q) + 1;
	} else {
		shost->sg_tablesize = ADV_MAX_SG_LIST;
	}

	/*
	 * The value of 'sg_tablesize' can not exceed the SCSI
	 * mid-level driver definition of SG_ALL. SG_ALL also
	 * must not be exceeded, because it is used to define the
	 * size of the scatter-gather table in 'struct asc_sg_head'.
	 */
	if (shost->sg_tablesize > SG_ALL) {
		shost->sg_tablesize = SG_ALL;
	}

	ASC_DBG(1, "sg_tablesize: %d\n", shost->sg_tablesize);

	/* BIOS start address. */
	if (ASC_NARROW_BOARD(boardp)) {
		shost->base = AscGetChipBiosAddress(asc_dvc_varp->iop_base,
						    asc_dvc_varp->bus_type);
	} else {
		/*
		 * Fill-in BIOS board variables. The Wide BIOS saves
		 * information in LRAM that is used by the driver.
		 */
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_SIGNATURE, boardp->bios_signature);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_VERSION, boardp->bios_version);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_CODESEG, boardp->bios_codeseg);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_CODELEN, boardp->bios_codelen);

		ASC_DBG(1, "bios_signature 0x%x, bios_version 0x%x\n",
			 boardp->bios_signature, boardp->bios_version);

		ASC_DBG(1, "bios_codeseg 0x%x, bios_codelen 0x%x\n",
			 boardp->bios_codeseg, boardp->bios_codelen);

		/*
		 * If the BIOS saved a valid signature, then fill in
		 * the BIOS code segment base address.
		 */
		if (boardp->bios_signature == 0x55AA) {
			/*
			 * Convert x86 realmode code segment to a linear
			 * address by shifting left 4.
			 */
			shost->base = ((ulong)boardp->bios_codeseg << 4);
		} else {
			shost->base = 0;
		}
	}

	/*
	 * Register Board Resources - I/O Port, DMA, IRQ
	 */

	/* Register DMA Channel for Narrow boards. */
	shost->dma_channel = NO_ISA_DMA;	/* Default to no ISA DMA. */
#ifdef CONFIG_ISA
	if (ASC_NARROW_BOARD(boardp)) {
		/* Register DMA channel for ISA bus. */
		if (asc_dvc_varp->bus_type & ASC_IS_ISA) {
			shost->dma_channel = asc_dvc_varp->cfg->isa_dma_channel;
			ret = request_dma(shost->dma_channel, DRV_NAME);
			if (ret) {
				shost_printk(KERN_ERR, shost, "request_dma() "
						"%d failed %d\n",
						shost->dma_channel, ret);
				goto err_unmap;
			}
			AscEnableIsaDma(shost->dma_channel);
		}
	}
#endif /* CONFIG_ISA */

	/* Register IRQ Number. */
	ASC_DBG(2, "request_irq(%d, %p)\n", boardp->irq, shost);

	ret = request_irq(boardp->irq, advansys_interrupt, share_irq,
			  DRV_NAME, shost);

	if (ret) {
		if (ret == -EBUSY) {
			shost_printk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"already in use\n", boardp->irq);
		} else if (ret == -EINVAL) {
			shost_printk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"not valid\n", boardp->irq);
		} else {
			shost_printk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"failed with %d\n", boardp->irq, ret);
		}
		goto err_free_dma;
	}

	/*
	 * Initialize board RISC chip and enable interrupts.
	 */
	if (ASC_NARROW_BOARD(boardp)) {
		ASC_DBG(2, "AscInitAsc1000Driver()\n");

		asc_dvc_varp->overrun_buf = kzalloc(ASC_OVERRUN_BSIZE, GFP_KERNEL);
		if (!asc_dvc_varp->overrun_buf) {
			ret = -ENOMEM;
			goto err_free_irq;
		}
		warn_code = AscInitAsc1000Driver(asc_dvc_varp);

		if (warn_code || asc_dvc_varp->err_code) {
			shost_printk(KERN_ERR, shost, "error: init_state 0x%x, "
					"warn 0x%x, error 0x%x\n",
					asc_dvc_varp->init_state, warn_code,
					asc_dvc_varp->err_code);
			if (!asc_dvc_varp->overrun_dma) {
				ret = -ENODEV;
				goto err_free_mem;
			}
		}
	} else {
		if (advansys_wide_init_chip(shost)) {
			ret = -ENODEV;
			goto err_free_mem;
		}
	}

	ASC_DBG_PRT_SCSI_HOST(2, shost);

	ret = scsi_add_host(shost, boardp->dev);
	if (ret)
		goto err_free_mem;

	scsi_scan_host(shost);
	return 0;

 err_free_mem:
	if (ASC_NARROW_BOARD(boardp)) {
		if (asc_dvc_varp->overrun_dma)
			dma_unmap_single(boardp->dev, asc_dvc_varp->overrun_dma,
					 ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
		kfree(asc_dvc_varp->overrun_buf);
	} else
		advansys_wide_free_mem(boardp);
 err_free_irq:
	free_irq(boardp->irq, shost);
 err_free_dma:
#ifdef CONFIG_ISA
	if (shost->dma_channel != NO_ISA_DMA)
		free_dma(shost->dma_channel);
#endif
 err_unmap:
	if (boardp->ioremap_addr)
		iounmap(boardp->ioremap_addr);
#ifdef CONFIG_PCI
 err_shost:
#endif
	return ret;
}