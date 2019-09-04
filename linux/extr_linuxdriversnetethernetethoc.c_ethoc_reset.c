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
struct ethoc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_ALL ; 
 int /*<<< orphan*/  IPGT ; 
 int /*<<< orphan*/  MODER ; 
 int MODER_CRC ; 
 int MODER_FULLD ; 
 int MODER_PAD ; 
 int /*<<< orphan*/  ethoc_ack_irq (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_disable_rx_and_tx (struct ethoc*) ; 
 int /*<<< orphan*/  ethoc_enable_irq (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_enable_rx_and_tx (struct ethoc*) ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ethoc_reset(struct ethoc *dev)
{
	u32 mode;

	/* TODO: reset controller? */

	ethoc_disable_rx_and_tx(dev);

	/* TODO: setup registers */

	/* enable FCS generation and automatic padding */
	mode = ethoc_read(dev, MODER);
	mode |= MODER_CRC | MODER_PAD;
	ethoc_write(dev, MODER, mode);

	/* set full-duplex mode */
	mode = ethoc_read(dev, MODER);
	mode |= MODER_FULLD;
	ethoc_write(dev, MODER, mode);
	ethoc_write(dev, IPGT, 0x15);

	ethoc_ack_irq(dev, INT_MASK_ALL);
	ethoc_enable_irq(dev, INT_MASK_ALL);
	ethoc_enable_rx_and_tx(dev);
	return 0;
}