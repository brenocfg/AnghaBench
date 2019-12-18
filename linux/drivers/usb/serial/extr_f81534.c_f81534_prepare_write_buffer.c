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
struct usb_serial_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; } ;
struct f81534_port_private {int phy_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  F81534_MAX_TX_SIZE ; 
 int F81534_NUM_PORT ; 
 int F81534_RECEIVE_BLOCK_SIZE ; 
 int F81534_TOKEN_WRITE ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct f81534_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void f81534_prepare_write_buffer(struct usb_serial_port *port, u8 *buf)
{
	struct f81534_port_private *port_priv = usb_get_serial_port_data(port);
	int phy_num = port_priv->phy_num;
	u8 tx_len;
	int i;

	/*
	 * The block layout is fixed with 4x128 Bytes, per 128 Bytes a port.
	 * index 0: port phy idx (e.g., 0,1,2,3)
	 * index 1: only F81534_TOKEN_WRITE
	 * index 2: serial TX out length
	 * index 3: fix to 0
	 * index 4~127: serial out data block
	 */
	for (i = 0; i < F81534_NUM_PORT; ++i) {
		buf[i * F81534_RECEIVE_BLOCK_SIZE] = i;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 1] = F81534_TOKEN_WRITE;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 2] = 0;
		buf[i * F81534_RECEIVE_BLOCK_SIZE + 3] = 0;
	}

	tx_len = kfifo_out_locked(&port->write_fifo,
				&buf[phy_num * F81534_RECEIVE_BLOCK_SIZE + 4],
				F81534_MAX_TX_SIZE, &port->lock);

	buf[phy_num * F81534_RECEIVE_BLOCK_SIZE + 2] = tx_len;
}