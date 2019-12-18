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
struct rt2x00_dev {int dummy; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
#define  QID_BEACON 129 
#define  QID_RX 128 
 int /*<<< orphan*/  TXRX_CSR19 ; 
 int /*<<< orphan*/  TXRX_CSR19_BEACON_GEN ; 
 int /*<<< orphan*/  TXRX_CSR19_TBCN ; 
 int /*<<< orphan*/  TXRX_CSR19_TSF_COUNT ; 
 int /*<<< orphan*/  TXRX_CSR2 ; 
 int /*<<< orphan*/  TXRX_CSR2_DISABLE_RX ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2500usb_stop_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u16 reg;

	switch (queue->qid) {
	case QID_RX:
		reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR2);
		rt2x00_set_field16(&reg, TXRX_CSR2_DISABLE_RX, 1);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR2, reg);
		break;
	case QID_BEACON:
		reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR19);
		rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 0);
		rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 0);
		rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR19, reg);
		break;
	default:
		break;
	}
}