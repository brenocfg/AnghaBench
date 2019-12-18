#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ktermios {int c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct tty_port {struct tty_struct* tty; } ;
struct TYPE_11__ {scalar_t__ membase; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct TYPE_10__ {int length; } ;
struct circ_buf {int /*<<< orphan*/  buf; } ;
struct lpuart_port {int rx_dma_rng_buf_len; TYPE_4__ port; int /*<<< orphan*/  dma_rx_chan; TYPE_6__* dma_rx_desc; int /*<<< orphan*/  dma_rx_cookie; TYPE_2__ rx_sgl; struct circ_buf rx_ring; } ;
struct dma_slave_config {int src_maxburst; int /*<<< orphan*/  direction; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  src_addr; } ;
struct TYPE_12__ {struct lpuart_port* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_9__ {struct tty_port port; } ;

/* Variables and functions */
 int CS7 ; 
 int CSIZE ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int DMA_RX_TIMEOUT ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PARENB ; 
 int /*<<< orphan*/  UARTBAUD ; 
 unsigned long UARTBAUD_RDMAE ; 
 scalar_t__ UARTCR5 ; 
 int UARTCR5_RDMAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_map_sg (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* dmaengine_prep_dma_cyclic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_6__*) ; 
 int fls (int) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long lpuart32_read (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (TYPE_4__*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_dma_datareg_addr (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_dma_rx_complete ; 
 scalar_t__ lpuart_is_32 (struct lpuart_port*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  sg_dma_address (TYPE_2__*) ; 
 int /*<<< orphan*/  sg_init_one (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static inline int lpuart_start_rx_dma(struct lpuart_port *sport)
{
	struct dma_slave_config dma_rx_sconfig = {};
	struct circ_buf *ring = &sport->rx_ring;
	int ret, nent;
	int bits, baud;
	struct tty_port *port = &sport->port.state->port;
	struct tty_struct *tty = port->tty;
	struct ktermios *termios = &tty->termios;

	baud = tty_get_baud_rate(tty);

	bits = (termios->c_cflag & CSIZE) == CS7 ? 9 : 10;
	if (termios->c_cflag & PARENB)
		bits++;

	/*
	 * Calculate length of one DMA buffer size to keep latency below
	 * 10ms at any baud rate.
	 */
	sport->rx_dma_rng_buf_len = (DMA_RX_TIMEOUT * baud /  bits / 1000) * 2;
	sport->rx_dma_rng_buf_len = (1 << (fls(sport->rx_dma_rng_buf_len) - 1));
	if (sport->rx_dma_rng_buf_len < 16)
		sport->rx_dma_rng_buf_len = 16;

	ring->buf = kzalloc(sport->rx_dma_rng_buf_len, GFP_ATOMIC);
	if (!ring->buf)
		return -ENOMEM;

	sg_init_one(&sport->rx_sgl, ring->buf, sport->rx_dma_rng_buf_len);
	nent = dma_map_sg(sport->port.dev, &sport->rx_sgl, 1, DMA_FROM_DEVICE);

	if (!nent) {
		dev_err(sport->port.dev, "DMA Rx mapping error\n");
		return -EINVAL;
	}

	dma_rx_sconfig.src_addr = lpuart_dma_datareg_addr(sport);
	dma_rx_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_rx_sconfig.src_maxburst = 1;
	dma_rx_sconfig.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(sport->dma_rx_chan, &dma_rx_sconfig);

	if (ret < 0) {
		dev_err(sport->port.dev,
				"DMA Rx slave config failed, err = %d\n", ret);
		return ret;
	}

	sport->dma_rx_desc = dmaengine_prep_dma_cyclic(sport->dma_rx_chan,
				 sg_dma_address(&sport->rx_sgl),
				 sport->rx_sgl.length,
				 sport->rx_sgl.length / 2,
				 DMA_DEV_TO_MEM,
				 DMA_PREP_INTERRUPT);
	if (!sport->dma_rx_desc) {
		dev_err(sport->port.dev, "Cannot prepare cyclic DMA\n");
		return -EFAULT;
	}

	sport->dma_rx_desc->callback = lpuart_dma_rx_complete;
	sport->dma_rx_desc->callback_param = sport;
	sport->dma_rx_cookie = dmaengine_submit(sport->dma_rx_desc);
	dma_async_issue_pending(sport->dma_rx_chan);

	if (lpuart_is_32(sport)) {
		unsigned long temp = lpuart32_read(&sport->port, UARTBAUD);

		lpuart32_write(&sport->port, temp | UARTBAUD_RDMAE, UARTBAUD);
	} else {
		writeb(readb(sport->port.membase + UARTCR5) | UARTCR5_RDMAS,
		       sport->port.membase + UARTCR5);
	}

	return 0;
}