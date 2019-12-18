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
struct uart_port {unsigned int line; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ head; scalar_t__ tail; } ;
struct TYPE_5__ {TYPE_1__ xmit; } ;
struct sirfsoc_uart_port {int ms_enabled; int is_hrt_enabled; int rx_period_time; int rx_last_pos; TYPE_3__* uart_reg; int /*<<< orphan*/  is_atlas7; scalar_t__ rx_dma_chan; int /*<<< orphan*/  hrt; TYPE_2__ rx_dma_items; scalar_t__ pio_fetch_cnt; int /*<<< orphan*/  cts_gpio; scalar_t__ hw_flow_ctrl; int /*<<< orphan*/  tx_dma_state; scalar_t__ tx_dma_chan; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_int_en_reg; int /*<<< orphan*/  sirfsoc_rx_fifo_op; int /*<<< orphan*/  sirfsoc_rx_dma_io_ctrl; int /*<<< orphan*/  sirfsoc_swh_dma_io; int /*<<< orphan*/  sirfsoc_tx_fifo_level_chk; int /*<<< orphan*/  sirfsoc_rx_fifo_level_chk; int /*<<< orphan*/  sirfsoc_rx_fifo_ctrl; int /*<<< orphan*/  sirfsoc_tx_fifo_ctrl; int /*<<< orphan*/  sirfsoc_tx_fifo_op; int /*<<< orphan*/  sirfsoc_mode1; int /*<<< orphan*/  sirfsoc_tx_rx_en; int /*<<< orphan*/  sirfsoc_rx_dma_io_len; int /*<<< orphan*/  sirfsoc_tx_dma_io_len; int /*<<< orphan*/  sirfsoc_tx_dma_io_ctrl; } ;
struct sirfsoc_int_en {int dummy; } ;
struct TYPE_6__ {scalar_t__ uart_type; struct sirfsoc_int_en uart_int_en; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 int SIRFSOC_USP_EN ; 
 int SIRFSOC_USP_ENDIAN_CTRL_LSBF ; 
 int SIRFSOC_USP_FRADDR_CLR_EN ; 
 int SIRFUART_CLEAR_RX_ADDR_EN ; 
 int SIRFUART_FIFO_RESET ; 
 int SIRFUART_FIFO_START ; 
 int SIRFUART_FIFO_THD (struct uart_port*) ; 
 int SIRFUART_IO_MODE ; 
 char* SIRFUART_PORT_NAME ; 
 int SIRFUART_RX_DMA_FLUSH ; 
 int SIRFUART_RX_EN ; 
 int SIRFUART_RX_FIFO_CHK_HC (unsigned int,int) ; 
 int SIRFUART_RX_FIFO_CHK_LC (unsigned int,int) ; 
 int SIRFUART_RX_FIFO_CHK_SC (unsigned int,int) ; 
 int SIRFUART_RX_IO_INT_EN (struct sirfsoc_int_en*,scalar_t__) ; 
 int SIRFUART_TX_EN ; 
 int SIRFUART_TX_FIFO_CHK_HC (unsigned int,int) ; 
 int SIRFUART_TX_FIFO_CHK_LC (unsigned int,int) ; 
 int SIRFUART_TX_FIFO_CHK_SC (unsigned int,int) ; 
 scalar_t__ SIRF_REAL_UART ; 
 scalar_t__ SIRF_USP_UART ; 
 int /*<<< orphan*/  TX_DMA_IDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sirfsoc_uart_port*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_modify_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct sirfsoc_uart_port*) ; 
 int /*<<< orphan*/  sirfsoc_uart_isr ; 
 int /*<<< orphan*/  sirfsoc_uart_start_next_rx_dma (struct uart_port*) ; 
 int /*<<< orphan*/  sirfsoc_uart_usp_cts_handler ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sirfsoc_uart_startup(struct uart_port *port)
{
	struct sirfsoc_uart_port *sirfport	= to_sirfport(port);
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_int_en *uint_en = &sirfport->uart_reg->uart_int_en;
	unsigned int index			= port->line;
	int ret;
	irq_modify_status(port->irq, IRQ_NOREQUEST, IRQ_NOAUTOEN);
	ret = request_irq(port->irq,
				sirfsoc_uart_isr,
				0,
				SIRFUART_PORT_NAME,
				sirfport);
	if (ret != 0) {
		dev_err(port->dev, "UART%d request IRQ line (%d) failed.\n",
							index, port->irq);
		goto irq_err;
	}
	/* initial hardware settings */
	wr_regl(port, ureg->sirfsoc_tx_dma_io_ctrl,
		rd_regl(port, ureg->sirfsoc_tx_dma_io_ctrl) |
		SIRFUART_IO_MODE);
	wr_regl(port, ureg->sirfsoc_rx_dma_io_ctrl,
		rd_regl(port, ureg->sirfsoc_rx_dma_io_ctrl) |
		SIRFUART_IO_MODE);
	wr_regl(port, ureg->sirfsoc_rx_dma_io_ctrl,
		rd_regl(port, ureg->sirfsoc_rx_dma_io_ctrl) &
		~SIRFUART_RX_DMA_FLUSH);
	wr_regl(port, ureg->sirfsoc_tx_dma_io_len, 0);
	wr_regl(port, ureg->sirfsoc_rx_dma_io_len, 0);
	wr_regl(port, ureg->sirfsoc_tx_rx_en, SIRFUART_RX_EN | SIRFUART_TX_EN);
	if (sirfport->uart_reg->uart_type == SIRF_USP_UART)
		wr_regl(port, ureg->sirfsoc_mode1,
			SIRFSOC_USP_ENDIAN_CTRL_LSBF |
			SIRFSOC_USP_EN);
	wr_regl(port, ureg->sirfsoc_tx_fifo_op, SIRFUART_FIFO_RESET);
	wr_regl(port, ureg->sirfsoc_rx_fifo_op, SIRFUART_FIFO_RESET);
	wr_regl(port, ureg->sirfsoc_rx_fifo_op, 0);
	wr_regl(port, ureg->sirfsoc_tx_fifo_ctrl, SIRFUART_FIFO_THD(port));
	wr_regl(port, ureg->sirfsoc_rx_fifo_ctrl, SIRFUART_FIFO_THD(port));
	if (sirfport->rx_dma_chan)
		wr_regl(port, ureg->sirfsoc_rx_fifo_level_chk,
			SIRFUART_RX_FIFO_CHK_SC(port->line, 0x1) |
			SIRFUART_RX_FIFO_CHK_LC(port->line, 0x2) |
			SIRFUART_RX_FIFO_CHK_HC(port->line, 0x4));
	if (sirfport->tx_dma_chan) {
		sirfport->tx_dma_state = TX_DMA_IDLE;
		wr_regl(port, ureg->sirfsoc_tx_fifo_level_chk,
				SIRFUART_TX_FIFO_CHK_SC(port->line, 0x1b) |
				SIRFUART_TX_FIFO_CHK_LC(port->line, 0xe) |
				SIRFUART_TX_FIFO_CHK_HC(port->line, 0x4));
	}
	sirfport->ms_enabled = false;
	if (sirfport->uart_reg->uart_type == SIRF_USP_UART &&
		sirfport->hw_flow_ctrl) {
		irq_modify_status(gpio_to_irq(sirfport->cts_gpio),
			IRQ_NOREQUEST, IRQ_NOAUTOEN);
		ret = request_irq(gpio_to_irq(sirfport->cts_gpio),
			sirfsoc_uart_usp_cts_handler, IRQF_TRIGGER_FALLING |
			IRQF_TRIGGER_RISING, "usp_cts_irq", sirfport);
		if (ret != 0) {
			dev_err(port->dev, "UART-USP:request gpio irq fail\n");
			goto init_rx_err;
		}
	}
	if (sirfport->uart_reg->uart_type == SIRF_REAL_UART &&
		sirfport->rx_dma_chan)
		wr_regl(port, ureg->sirfsoc_swh_dma_io,
			SIRFUART_CLEAR_RX_ADDR_EN);
	if (sirfport->uart_reg->uart_type == SIRF_USP_UART &&
			sirfport->rx_dma_chan)
		wr_regl(port, ureg->sirfsoc_rx_dma_io_ctrl,
			rd_regl(port, ureg->sirfsoc_rx_dma_io_ctrl) |
			SIRFSOC_USP_FRADDR_CLR_EN);
	if (sirfport->rx_dma_chan && !sirfport->is_hrt_enabled) {
		sirfport->is_hrt_enabled = true;
		sirfport->rx_period_time = 20000000;
		sirfport->rx_last_pos = -1;
		sirfport->pio_fetch_cnt = 0;
		sirfport->rx_dma_items.xmit.tail =
			sirfport->rx_dma_items.xmit.head = 0;
		hrtimer_start(&sirfport->hrt,
			ns_to_ktime(sirfport->rx_period_time),
			HRTIMER_MODE_REL);
	}
	wr_regl(port, ureg->sirfsoc_rx_fifo_op, SIRFUART_FIFO_START);
	if (sirfport->rx_dma_chan)
		sirfsoc_uart_start_next_rx_dma(port);
	else {
		if (!sirfport->is_atlas7)
			wr_regl(port, ureg->sirfsoc_int_en_reg,
				rd_regl(port, ureg->sirfsoc_int_en_reg) |
				SIRFUART_RX_IO_INT_EN(uint_en,
					sirfport->uart_reg->uart_type));
		else
			wr_regl(port, ureg->sirfsoc_int_en_reg,
				SIRFUART_RX_IO_INT_EN(uint_en,
					sirfport->uart_reg->uart_type));
	}
	enable_irq(port->irq);

	return 0;
init_rx_err:
	free_irq(port->irq, sirfport);
irq_err:
	return ret;
}