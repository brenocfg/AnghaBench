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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pciefd_board {int can_count; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  cmd_lock; struct pci_dev* pci_dev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIEFD_BAR0_SIZE ; 
 int /*<<< orphan*/  PCIEFD_DRV_NAME ; 
 scalar_t__ PCIEFD_FW_VERSION (int,int,int) ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_CTL_CLR ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_CTL_SET ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_VER1 ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_VER2 ; 
 int /*<<< orphan*/  PCIEFD_SYS_CTL_CLK_EN ; 
 int /*<<< orphan*/  PCIEFD_SYS_CTL_TS_RST ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  can ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct pciefd_board* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pciefd_board*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcibios_err_to_errno (int) ; 
 int pciefd_can_probe (struct pciefd_board*) ; 
 int /*<<< orphan*/  pciefd_can_remove_all (struct pciefd_board*) ; 
 int pciefd_sys_readreg (struct pciefd_board*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_sys_writereg (struct pciefd_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct pciefd_board*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int peak_pciefd_probe(struct pci_dev *pdev,
			     const struct pci_device_id *ent)
{
	struct pciefd_board *pciefd;
	int err, can_count;
	u16 sub_sys_id;
	u8 hw_ver_major;
	u8 hw_ver_minor;
	u8 hw_ver_sub;
	u32 v2;

	err = pci_enable_device(pdev);
	if (err)
		return err;
	err = pci_request_regions(pdev, PCIEFD_DRV_NAME);
	if (err)
		goto err_disable_pci;

	/* the number of channels depends on sub-system id */
	err = pci_read_config_word(pdev, PCI_SUBSYSTEM_ID, &sub_sys_id);
	if (err)
		goto err_release_regions;

	dev_dbg(&pdev->dev, "probing device %04x:%04x:%04x\n",
		pdev->vendor, pdev->device, sub_sys_id);

	if (sub_sys_id >= 0x0012)
		can_count = 4;
	else if (sub_sys_id >= 0x0010)
		can_count = 3;
	else if (sub_sys_id >= 0x0004)
		can_count = 2;
	else
		can_count = 1;

	/* allocate board structure object */
	pciefd = devm_kzalloc(&pdev->dev, struct_size(pciefd, can, can_count),
			      GFP_KERNEL);
	if (!pciefd) {
		err = -ENOMEM;
		goto err_release_regions;
	}

	/* initialize the board structure */
	pciefd->pci_dev = pdev;
	spin_lock_init(&pciefd->cmd_lock);

	/* save the PCI BAR0 virtual address for further system regs access */
	pciefd->reg_base = pci_iomap(pdev, 0, PCIEFD_BAR0_SIZE);
	if (!pciefd->reg_base) {
		dev_err(&pdev->dev, "failed to map PCI resource #0\n");
		err = -ENOMEM;
		goto err_release_regions;
	}

	/* read the firmware version number */
	v2 = pciefd_sys_readreg(pciefd, PCIEFD_REG_SYS_VER2);

	hw_ver_major = (v2 & 0x0000f000) >> 12;
	hw_ver_minor = (v2 & 0x00000f00) >> 8;
	hw_ver_sub = (v2 & 0x000000f0) >> 4;

	dev_info(&pdev->dev,
		 "%ux CAN-FD PCAN-PCIe FPGA v%u.%u.%u:\n", can_count,
		 hw_ver_major, hw_ver_minor, hw_ver_sub);

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	/* FW < v3.3.0 DMA logic doesn't handle correctly the mix of 32-bit and
	 * 64-bit logical addresses: this workaround forces usage of 32-bit
	 * DMA addresses only when such a fw is detected.
	 */
	if (PCIEFD_FW_VERSION(hw_ver_major, hw_ver_minor, hw_ver_sub) <
	    PCIEFD_FW_VERSION(3, 3, 0)) {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err)
			dev_warn(&pdev->dev,
				 "warning: can't set DMA mask %llxh (err %d)\n",
				 DMA_BIT_MASK(32), err);
	}
#endif

	/* stop system clock */
	pciefd_sys_writereg(pciefd, PCIEFD_SYS_CTL_CLK_EN,
			    PCIEFD_REG_SYS_CTL_CLR);

	pci_set_master(pdev);

	/* create now the corresponding channels objects */
	while (pciefd->can_count < can_count) {
		err = pciefd_can_probe(pciefd);
		if (err)
			goto err_free_canfd;

		pciefd->can_count++;
	}

	/* set system timestamps counter in RST mode */
	pciefd_sys_writereg(pciefd, PCIEFD_SYS_CTL_TS_RST,
			    PCIEFD_REG_SYS_CTL_SET);

	/* wait a bit (read cycle) */
	(void)pciefd_sys_readreg(pciefd, PCIEFD_REG_SYS_VER1);

	/* free all clocks */
	pciefd_sys_writereg(pciefd, PCIEFD_SYS_CTL_TS_RST,
			    PCIEFD_REG_SYS_CTL_CLR);

	/* start system clock */
	pciefd_sys_writereg(pciefd, PCIEFD_SYS_CTL_CLK_EN,
			    PCIEFD_REG_SYS_CTL_SET);

	/* remember the board structure address in the device user data */
	pci_set_drvdata(pdev, pciefd);

	return 0;

err_free_canfd:
	pciefd_can_remove_all(pciefd);

	pci_iounmap(pdev, pciefd->reg_base);

err_release_regions:
	pci_release_regions(pdev);

err_disable_pci:
	pci_disable_device(pdev);

	/* pci_xxx_config_word() return positive PCIBIOS_xxx error codes while
	 * the probe() function must return a negative errno in case of failure
	 * (err is unchanged if negative) */
	return pcibios_err_to_errno(err);
}