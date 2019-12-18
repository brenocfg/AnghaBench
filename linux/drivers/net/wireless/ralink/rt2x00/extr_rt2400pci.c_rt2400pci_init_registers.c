#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rt2x00_dev {TYPE_3__* ops; TYPE_1__* rx; } ;
struct TYPE_6__ {TYPE_2__* lib; } ;
struct TYPE_5__ {scalar_t__ (* set_device_state ) (struct rt2x00_dev*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSR0 ; 
 int /*<<< orphan*/  ARCSR0_AR_BBP_DATA0 ; 
 int /*<<< orphan*/  ARCSR0_AR_BBP_DATA1 ; 
 int /*<<< orphan*/  ARCSR0_AR_BBP_ID0 ; 
 int /*<<< orphan*/  ARCSR0_AR_BBP_ID1 ; 
 int /*<<< orphan*/  CNT0 ; 
 int /*<<< orphan*/  CNT3 ; 
 int /*<<< orphan*/  CNT4 ; 
 int /*<<< orphan*/  CSR1 ; 
 int /*<<< orphan*/  CSR14 ; 
 int /*<<< orphan*/  CSR14_BEACON_GEN ; 
 int /*<<< orphan*/  CSR14_CFP_COUNT_PRELOAD ; 
 int /*<<< orphan*/  CSR14_TATIMW ; 
 int /*<<< orphan*/  CSR14_TBCM_PRELOAD ; 
 int /*<<< orphan*/  CSR14_TBCN ; 
 int /*<<< orphan*/  CSR14_TCFP ; 
 int /*<<< orphan*/  CSR14_TSF_COUNT ; 
 int /*<<< orphan*/  CSR14_TSF_SYNC ; 
 int /*<<< orphan*/  CSR1_BBP_RESET ; 
 int /*<<< orphan*/  CSR1_HOST_READY ; 
 int /*<<< orphan*/  CSR1_SOFT_RESET ; 
 int /*<<< orphan*/  CSR9 ; 
 int /*<<< orphan*/  CSR9_MAX_FRAME_UNIT ; 
 int EBUSY ; 
 int /*<<< orphan*/  MACCSR0 ; 
 int /*<<< orphan*/  MACCSR1 ; 
 int /*<<< orphan*/  MACCSR2 ; 
 int /*<<< orphan*/  MACCSR2_DELAY ; 
 int /*<<< orphan*/  PSCSR0 ; 
 int /*<<< orphan*/  PSCSR1 ; 
 int /*<<< orphan*/  PSCSR2 ; 
 int /*<<< orphan*/  PSCSR3 ; 
 int /*<<< orphan*/  PWRCSR0 ; 
 int /*<<< orphan*/  RALINKCSR ; 
 int /*<<< orphan*/  RALINKCSR_AR_BBP_DATA0 ; 
 int /*<<< orphan*/  RALINKCSR_AR_BBP_DATA1 ; 
 int /*<<< orphan*/  RALINKCSR_AR_BBP_ID0 ; 
 int /*<<< orphan*/  RALINKCSR_AR_BBP_ID1 ; 
 int /*<<< orphan*/  RXCSR3 ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID0 ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID0_VALID ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID1 ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID1_VALID ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID2 ; 
 int /*<<< orphan*/  RXCSR3_BBP_ID2_VALID ; 
 int /*<<< orphan*/  STATE_AWAKE ; 
 int /*<<< orphan*/  TIMECSR ; 
 int /*<<< orphan*/  TIMECSR_BEACON_EXPECT ; 
 int /*<<< orphan*/  TIMECSR_US_64_COUNT ; 
 int /*<<< orphan*/  TIMECSR_US_COUNT ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2400pci_init_registers(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	rt2x00mmio_register_write(rt2x00dev, PSCSR0, 0x00020002);
	rt2x00mmio_register_write(rt2x00dev, PSCSR1, 0x00000002);
	rt2x00mmio_register_write(rt2x00dev, PSCSR2, 0x00023f20);
	rt2x00mmio_register_write(rt2x00dev, PSCSR3, 0x00000002);

	reg = rt2x00mmio_register_read(rt2x00dev, TIMECSR);
	rt2x00_set_field32(&reg, TIMECSR_US_COUNT, 33);
	rt2x00_set_field32(&reg, TIMECSR_US_64_COUNT, 63);
	rt2x00_set_field32(&reg, TIMECSR_BEACON_EXPECT, 0);
	rt2x00mmio_register_write(rt2x00dev, TIMECSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, CSR9);
	rt2x00_set_field32(&reg, CSR9_MAX_FRAME_UNIT,
			   (rt2x00dev->rx->data_size / 128));
	rt2x00mmio_register_write(rt2x00dev, CSR9, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, CSR14);
	rt2x00_set_field32(&reg, CSR14_TSF_COUNT, 0);
	rt2x00_set_field32(&reg, CSR14_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, CSR14_TBCN, 0);
	rt2x00_set_field32(&reg, CSR14_TCFP, 0);
	rt2x00_set_field32(&reg, CSR14_TATIMW, 0);
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, CSR14_CFP_COUNT_PRELOAD, 0);
	rt2x00_set_field32(&reg, CSR14_TBCM_PRELOAD, 0);
	rt2x00mmio_register_write(rt2x00dev, CSR14, reg);

	rt2x00mmio_register_write(rt2x00dev, CNT3, 0x3f080000);

	reg = rt2x00mmio_register_read(rt2x00dev, ARCSR0);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_DATA0, 133);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_ID0, 134);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_DATA1, 136);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_ID1, 135);
	rt2x00mmio_register_write(rt2x00dev, ARCSR0, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, RXCSR3);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0, 3); /* Tx power.*/
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1, 32); /* Signal */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2, 36); /* Rssi */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2_VALID, 1);
	rt2x00mmio_register_write(rt2x00dev, RXCSR3, reg);

	rt2x00mmio_register_write(rt2x00dev, PWRCSR0, 0x3f3b3100);

	if (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		return -EBUSY;

	rt2x00mmio_register_write(rt2x00dev, MACCSR0, 0x00217223);
	rt2x00mmio_register_write(rt2x00dev, MACCSR1, 0x00235518);

	reg = rt2x00mmio_register_read(rt2x00dev, MACCSR2);
	rt2x00_set_field32(&reg, MACCSR2_DELAY, 64);
	rt2x00mmio_register_write(rt2x00dev, MACCSR2, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, RALINKCSR);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA0, 17);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID0, 154);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA1, 0);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID1, 154);
	rt2x00mmio_register_write(rt2x00dev, RALINKCSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, CSR1);
	rt2x00_set_field32(&reg, CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, CSR1_BBP_RESET, 0);
	rt2x00_set_field32(&reg, CSR1_HOST_READY, 0);
	rt2x00mmio_register_write(rt2x00dev, CSR1, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, CSR1);
	rt2x00_set_field32(&reg, CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, CSR1_HOST_READY, 1);
	rt2x00mmio_register_write(rt2x00dev, CSR1, reg);

	/*
	 * We must clear the FCS and FIFO error count.
	 * These registers are cleared on read,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, CNT0);
	reg = rt2x00mmio_register_read(rt2x00dev, CNT4);

	return 0;
}