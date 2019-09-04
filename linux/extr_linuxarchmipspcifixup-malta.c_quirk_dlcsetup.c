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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIIX4_FUNC0_DLC ; 
 int PIIX4_FUNC0_DLC_DELAYED_TRANSACTION_EN ; 
 int PIIX4_FUNC0_DLC_PASSIVE_RELEASE_EN ; 
 int PIIX4_FUNC0_DLC_USBPR_EN ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void quirk_dlcsetup(struct pci_dev *dev)
{
	u8 odlc, ndlc;

	(void) pci_read_config_byte(dev, PIIX4_FUNC0_DLC, &odlc);
	/* Enable passive releases and delayed transaction */
	ndlc = odlc | PIIX4_FUNC0_DLC_USBPR_EN |
		      PIIX4_FUNC0_DLC_PASSIVE_RELEASE_EN |
		      PIIX4_FUNC0_DLC_DELAYED_TRANSACTION_EN;
	(void) pci_write_config_byte(dev, PIIX4_FUNC0_DLC, ndlc);
}