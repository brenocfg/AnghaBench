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
typedef  scalar_t__ u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ide_host {int /*<<< orphan*/ ** dev; struct hpt_info* host_priv; } ;
struct hpt_info {scalar_t__ chip_type; } ;

/* Variables and functions */
 scalar_t__ HPT370 ; 
 scalar_t__ HPT374 ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hpt3xx_disable_fast_irq(struct pci_dev *dev, u8 mcr_addr)
{
	struct ide_host *host	= pci_get_drvdata(dev);
	struct hpt_info *info	= host->host_priv + (&dev->dev == host->dev[1]);
	u8  chip_type		= info->chip_type;
	u8  new_mcr, old_mcr	= 0;

	/*
	 * Disable the "fast interrupt" prediction.  Don't hold off
	 * on interrupts. (== 0x01 despite what the docs say)
	 */
	pci_read_config_byte(dev, mcr_addr + 1, &old_mcr);

	if (chip_type >= HPT374)
		new_mcr = old_mcr & ~0x07;
	else if (chip_type >= HPT370) {
		new_mcr = old_mcr;
		new_mcr &= ~0x02;
#ifdef HPT_DELAY_INTERRUPT
		new_mcr &= ~0x01;
#else
		new_mcr |=  0x01;
#endif
	} else					/* HPT366 and HPT368  */
		new_mcr = old_mcr & ~0x80;

	if (new_mcr != old_mcr)
		pci_write_config_byte(dev, mcr_addr + 1, new_mcr);
}