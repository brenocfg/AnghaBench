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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ssb_bus {scalar_t__ bustype; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int /*<<< orphan*/  PCI_STATUS_SIG_TARGET_ABORT ; 
 scalar_t__ SSB_BUSTYPE_PCI ; 
 int /*<<< orphan*/  SSB_GPIO_IN ; 
 int /*<<< orphan*/  SSB_GPIO_OUT ; 
 int /*<<< orphan*/  SSB_GPIO_OUT_ENABLE ; 
 int SSB_GPIO_PLL ; 
 int SSB_GPIO_XTAL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ssb_pci_xtal(struct ssb_bus *bus, u32 what, int turn_on)
{
	int err;
	u32 in, out, outenable;
	u16 pci_status;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		return 0;

	err = pci_read_config_dword(bus->host_pci, SSB_GPIO_IN, &in);
	if (err)
		goto err_pci;
	err = pci_read_config_dword(bus->host_pci, SSB_GPIO_OUT, &out);
	if (err)
		goto err_pci;
	err = pci_read_config_dword(bus->host_pci, SSB_GPIO_OUT_ENABLE, &outenable);
	if (err)
		goto err_pci;

	outenable |= what;

	if (turn_on) {
		/* Avoid glitching the clock if GPRS is already using it.
		 * We can't actually read the state of the PLLPD so we infer it
		 * by the value of XTAL_PU which *is* readable via gpioin.
		 */
		if (!(in & SSB_GPIO_XTAL)) {
			if (what & SSB_GPIO_XTAL) {
				/* Turn the crystal on */
				out |= SSB_GPIO_XTAL;
				if (what & SSB_GPIO_PLL)
					out |= SSB_GPIO_PLL;
				err = pci_write_config_dword(bus->host_pci, SSB_GPIO_OUT, out);
				if (err)
					goto err_pci;
				err = pci_write_config_dword(bus->host_pci, SSB_GPIO_OUT_ENABLE,
							     outenable);
				if (err)
					goto err_pci;
				msleep(1);
			}
			if (what & SSB_GPIO_PLL) {
				/* Turn the PLL on */
				out &= ~SSB_GPIO_PLL;
				err = pci_write_config_dword(bus->host_pci, SSB_GPIO_OUT, out);
				if (err)
					goto err_pci;
				msleep(5);
			}
		}

		err = pci_read_config_word(bus->host_pci, PCI_STATUS, &pci_status);
		if (err)
			goto err_pci;
		pci_status &= ~PCI_STATUS_SIG_TARGET_ABORT;
		err = pci_write_config_word(bus->host_pci, PCI_STATUS, pci_status);
		if (err)
			goto err_pci;
	} else {
		if (what & SSB_GPIO_XTAL) {
			/* Turn the crystal off */
			out &= ~SSB_GPIO_XTAL;
		}
		if (what & SSB_GPIO_PLL) {
			/* Turn the PLL off */
			out |= SSB_GPIO_PLL;
		}
		err = pci_write_config_dword(bus->host_pci, SSB_GPIO_OUT, out);
		if (err)
			goto err_pci;
		err = pci_write_config_dword(bus->host_pci, SSB_GPIO_OUT_ENABLE, outenable);
		if (err)
			goto err_pci;
	}

out:
	return err;

err_pci:
	pr_err("Error: ssb_pci_xtal() could not access PCI config space!\n");
	err = -EBUSY;
	goto out;
}