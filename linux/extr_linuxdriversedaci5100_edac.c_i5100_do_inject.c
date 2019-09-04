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
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int inject_hlinesel; int inject_eccmask1; int inject_deviceptr2; int inject_deviceptr1; scalar_t__ inject_channel; int /*<<< orphan*/  einj; int /*<<< orphan*/  mc; int /*<<< orphan*/  inject_eccmask2; } ;

/* Variables and functions */
 int /*<<< orphan*/  I5100_DINJ0 ; 
 int /*<<< orphan*/  I5100_MEM0EINJMSK0 ; 
 int /*<<< orphan*/  I5100_MEM0EINJMSK1 ; 
 int /*<<< orphan*/  I5100_MEM1EINJMSK0 ; 
 int /*<<< orphan*/  I5100_MEM1EINJMSK1 ; 
 int I5100_MEMXEINJMSK0_EINJEN ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i5100_do_inject(struct mem_ctl_info *mci)
{
	struct i5100_priv *priv = mci->pvt_info;
	u32 mask0;
	u16 mask1;

	/* MEM[1:0]EINJMSK0
	 * 31    - ADDRMATCHEN
	 * 29:28 - HLINESEL
	 *         00 Reserved
	 *         01 Lower half of cache line
	 *         10 Upper half of cache line
	 *         11 Both upper and lower parts of cache line
	 * 27    - EINJEN
	 * 25:19 - XORMASK1 for deviceptr1
	 * 9:5   - SEC2RAM for deviceptr2
	 * 4:0   - FIR2RAM for deviceptr1
	 */
	mask0 = ((priv->inject_hlinesel & 0x3) << 28) |
		I5100_MEMXEINJMSK0_EINJEN |
		((priv->inject_eccmask1 & 0xffff) << 10) |
		((priv->inject_deviceptr2 & 0x1f) << 5) |
		(priv->inject_deviceptr1 & 0x1f);

	/* MEM[1:0]EINJMSK1
	 * 15:0  - XORMASK2 for deviceptr2
	 */
	mask1 = priv->inject_eccmask2;

	if (priv->inject_channel == 0) {
		pci_write_config_dword(priv->mc, I5100_MEM0EINJMSK0, mask0);
		pci_write_config_word(priv->mc, I5100_MEM0EINJMSK1, mask1);
	} else {
		pci_write_config_dword(priv->mc, I5100_MEM1EINJMSK0, mask0);
		pci_write_config_word(priv->mc, I5100_MEM1EINJMSK1, mask1);
	}

	/* Error Injection Response Function
	 * Intel 5100 Memory Controller Hub Chipset (318378) datasheet
	 * hints about this register but carry no data about them. All
	 * data regarding device 19 is based on experimentation and the
	 * Intel 7300 Chipset Memory Controller Hub (318082) datasheet
	 * which appears to be accurate for the i5100 in this area.
	 *
	 * The injection code don't work without setting this register.
	 * The register needs to be flipped off then on else the hardware
	 * will only preform the first injection.
	 *
	 * Stop condition bits 7:4
	 * 1010 - Stop after one injection
	 * 1011 - Never stop injecting faults
	 *
	 * Start condition bits 3:0
	 * 1010 - Never start
	 * 1011 - Start immediately
	 */
	pci_write_config_byte(priv->einj, I5100_DINJ0, 0xaa);
	pci_write_config_byte(priv->einj, I5100_DINJ0, 0xab);
}