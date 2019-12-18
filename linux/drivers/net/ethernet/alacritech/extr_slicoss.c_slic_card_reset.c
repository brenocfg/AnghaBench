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
typedef  int /*<<< orphan*/  u16 ;
struct slic_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  SLIC_REG_RESET ; 
 int /*<<< orphan*/  SLIC_RESET_MAGIC ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_card_reset(struct slic_device *sdev)
{
	u16 cmd;

	slic_write(sdev, SLIC_REG_RESET, SLIC_RESET_MAGIC);
	/* flush write by means of config space */
	pci_read_config_word(sdev->pdev, PCI_COMMAND, &cmd);
	mdelay(1);
}