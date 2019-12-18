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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_IMAGE_BASE ; 
 int /*<<< orphan*/  H2M_BBP_AGENT ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  PBF_SYS_CTRL ; 
 int /*<<< orphan*/  PBF_SYS_CTRL_HOST_RAM_WRITE ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt2800pci_write_firmware(struct rt2x00_dev *rt2x00dev,
				    const u8 *data, const size_t len)
{
	u32 reg;

	/*
	 * enable Host program ram write selection
	 */
	reg = 0;
	rt2x00_set_field32(&reg, PBF_SYS_CTRL_HOST_RAM_WRITE, 1);
	rt2x00mmio_register_write(rt2x00dev, PBF_SYS_CTRL, reg);

	/*
	 * Write firmware to device.
	 */
	rt2x00mmio_register_multiwrite(rt2x00dev, FIRMWARE_IMAGE_BASE,
				       data, len);

	rt2x00mmio_register_write(rt2x00dev, PBF_SYS_CTRL, 0x00000);
	rt2x00mmio_register_write(rt2x00dev, PBF_SYS_CTRL, 0x00001);

	rt2x00mmio_register_write(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);

	return 0;
}