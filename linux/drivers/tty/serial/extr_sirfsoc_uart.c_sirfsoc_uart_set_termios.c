#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct uart_port {unsigned long uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct sirfsoc_uart_port {int rx_period_time; scalar_t__ rx_dma_chan; scalar_t__ tx_dma_chan; TYPE_1__* uart_reg; scalar_t__ ms_enabled; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_tx_rx_en; int /*<<< orphan*/  sirfsoc_tx_fifo_op; int /*<<< orphan*/  sirfsoc_rx_fifo_ctrl; int /*<<< orphan*/  sirfsoc_tx_fifo_ctrl; int /*<<< orphan*/  sirfsoc_rx_dma_io_ctrl; int /*<<< orphan*/  sirfsoc_tx_dma_io_ctrl; int /*<<< orphan*/  sirfsoc_async_param_reg; int /*<<< orphan*/  sirfsoc_rx_frame_ctrl; int /*<<< orphan*/  sirfsoc_tx_frame_ctrl; int /*<<< orphan*/  sirfsoc_line_ctrl; int /*<<< orphan*/  sirfsoc_mode2; int /*<<< orphan*/  sirfsoc_divisor; } ;
struct sirfsoc_int_en {int sirfsoc_rx_oflow_en; int sirfsoc_frm_err_en; int sirfsoc_parity_err_en; int sirfsoc_rxd_brk_en; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_4__ {unsigned long baud_rate; unsigned int reg_val; } ;
struct TYPE_3__ {scalar_t__ uart_type; struct sirfsoc_int_en uart_int_en; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 unsigned long SIRFSOC_UART_RX_TIMEOUT (unsigned long,int) ; 
 unsigned long SIRFSOC_USP_ASYNC_DIV2_MASK ; 
 unsigned long SIRFSOC_USP_ASYNC_DIV2_OFFSET ; 
 unsigned int SIRFSOC_USP_MODE2_CLK_DIVISOR_MASK ; 
 unsigned int SIRFSOC_USP_MODE2_CLK_DIVISOR_OFFSET ; 
 int SIRFSOC_USP_MODE2_RXD_DELAY_OFFSET ; 
 int SIRFSOC_USP_MODE2_TXD_DELAY_OFFSET ; 
 unsigned int SIRFSOC_USP_RX_CLK_DIVISOR_OFFSET ; 
 unsigned int SIRFSOC_USP_RX_DATA_LEN_OFFSET ; 
 unsigned int SIRFSOC_USP_RX_FRAME_LEN_OFFSET ; 
 unsigned int SIRFSOC_USP_RX_SHIFTER_LEN_OFFSET ; 
 unsigned int SIRFSOC_USP_TX_CLK_DIVISOR_OFFSET ; 
 unsigned int SIRFSOC_USP_TX_DATA_LEN_OFFSET ; 
 unsigned int SIRFSOC_USP_TX_FRAME_LEN_OFFSET ; 
 unsigned int SIRFSOC_USP_TX_SHIFTER_LEN_OFFSET ; 
 unsigned long SIRFUART_DATA_BIT_LEN_5 ; 
 unsigned long SIRFUART_DATA_BIT_LEN_6 ; 
 unsigned long SIRFUART_DATA_BIT_LEN_7 ; 
 unsigned long SIRFUART_DATA_BIT_LEN_8 ; 
 unsigned long SIRFUART_DMA_MODE ; 
 int SIRFUART_DUMMY_READ ; 
 unsigned long SIRFUART_FIFO_START ; 
 int SIRFUART_FIFO_THD (struct uart_port*) ; 
 unsigned long SIRFUART_IO_MODE ; 
 unsigned long SIRFUART_RECV_TIMEOUT_VALUE (unsigned long) ; 
 unsigned long SIRFUART_RX_EN ; 
 unsigned long SIRFUART_STICK_BIT_EVEN ; 
 unsigned long SIRFUART_STICK_BIT_MARK ; 
 unsigned long SIRFUART_STICK_BIT_ODD ; 
 unsigned long SIRFUART_STICK_BIT_SPACE ; 
 unsigned long SIRFUART_STOP_BIT_LEN_2 ; 
 unsigned long SIRFUART_TX_EN ; 
 unsigned long SIRFUART_UART_RECV_TIMEOUT (unsigned long) ; 
 unsigned long SIRFUART_USP_RECV_TIMEOUT (unsigned long) ; 
 unsigned long SIRF_BAUD_RATE_SUPPORT_NR ; 
 scalar_t__ SIRF_REAL_UART ; 
 scalar_t__ UART_ENABLE_MS (struct uart_port*,int) ; 
 TYPE_2__* baudrate_to_regv ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int sirfsoc_uart_calc_sample_div (unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  sirfsoc_uart_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  sirfsoc_uart_enable_ms (struct uart_port*) ; 
 unsigned int sirfsoc_usp_calc_sample_div (unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned long,unsigned long) ; 
 unsigned long uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sirfsoc_uart_set_termios(struct uart_port *port,
				       struct ktermios *termios,
				       struct ktermios *old)
{
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_int_en *uint_en = &sirfport->uart_reg->uart_int_en;
	unsigned long	config_reg = 0;
	unsigned long	baud_rate;
	unsigned long	set_baud;
	unsigned long	flags;
	unsigned long	ic;
	unsigned int	clk_div_reg = 0;
	unsigned long	txfifo_op_reg, ioclk_rate;
	unsigned long	rx_time_out;
	int		threshold_div;
	u32		data_bit_len, stop_bit_len, len_val;
	unsigned long	sample_div_reg = 0xf;
	ioclk_rate	= port->uartclk;

	switch (termios->c_cflag & CSIZE) {
	default:
	case CS8:
		data_bit_len = 8;
		config_reg |= SIRFUART_DATA_BIT_LEN_8;
		break;
	case CS7:
		data_bit_len = 7;
		config_reg |= SIRFUART_DATA_BIT_LEN_7;
		break;
	case CS6:
		data_bit_len = 6;
		config_reg |= SIRFUART_DATA_BIT_LEN_6;
		break;
	case CS5:
		data_bit_len = 5;
		config_reg |= SIRFUART_DATA_BIT_LEN_5;
		break;
	}
	if (termios->c_cflag & CSTOPB) {
		config_reg |= SIRFUART_STOP_BIT_LEN_2;
		stop_bit_len = 2;
	} else
		stop_bit_len = 1;

	spin_lock_irqsave(&port->lock, flags);
	port->read_status_mask = uint_en->sirfsoc_rx_oflow_en;
	port->ignore_status_mask = 0;
	if (sirfport->uart_reg->uart_type == SIRF_REAL_UART) {
		if (termios->c_iflag & INPCK)
			port->read_status_mask |= uint_en->sirfsoc_frm_err_en |
				uint_en->sirfsoc_parity_err_en;
	} else {
		if (termios->c_iflag & INPCK)
			port->read_status_mask |= uint_en->sirfsoc_frm_err_en;
	}
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
			port->read_status_mask |= uint_en->sirfsoc_rxd_brk_en;
	if (sirfport->uart_reg->uart_type == SIRF_REAL_UART) {
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |=
				uint_en->sirfsoc_frm_err_en |
				uint_en->sirfsoc_parity_err_en;
		if (termios->c_cflag & PARENB) {
			if (termios->c_cflag & CMSPAR) {
				if (termios->c_cflag & PARODD)
					config_reg |= SIRFUART_STICK_BIT_MARK;
				else
					config_reg |= SIRFUART_STICK_BIT_SPACE;
			} else {
				if (termios->c_cflag & PARODD)
					config_reg |= SIRFUART_STICK_BIT_ODD;
				else
					config_reg |= SIRFUART_STICK_BIT_EVEN;
			}
		}
	} else {
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |=
				uint_en->sirfsoc_frm_err_en;
		if (termios->c_cflag & PARENB)
			dev_warn(port->dev,
					"USP-UART not support parity err\n");
	}
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |=
			uint_en->sirfsoc_rxd_brk_en;
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |=
				uint_en->sirfsoc_rx_oflow_en;
	}
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= SIRFUART_DUMMY_READ;
	/* Hardware Flow Control Settings */
	if (UART_ENABLE_MS(port, termios->c_cflag)) {
		if (!sirfport->ms_enabled)
			sirfsoc_uart_enable_ms(port);
	} else {
		if (sirfport->ms_enabled)
			sirfsoc_uart_disable_ms(port);
	}
	baud_rate = uart_get_baud_rate(port, termios, old, 0, 4000000);
	if (ioclk_rate == 150000000) {
		for (ic = 0; ic < SIRF_BAUD_RATE_SUPPORT_NR; ic++)
			if (baud_rate == baudrate_to_regv[ic].baud_rate)
				clk_div_reg = baudrate_to_regv[ic].reg_val;
	}
	set_baud = baud_rate;
	if (sirfport->uart_reg->uart_type == SIRF_REAL_UART) {
		if (unlikely(clk_div_reg == 0))
			clk_div_reg = sirfsoc_uart_calc_sample_div(baud_rate,
					ioclk_rate, &set_baud);
		wr_regl(port, ureg->sirfsoc_divisor, clk_div_reg);
	} else {
		clk_div_reg = sirfsoc_usp_calc_sample_div(baud_rate,
				ioclk_rate, &sample_div_reg);
		sample_div_reg--;
		set_baud = ((ioclk_rate / (clk_div_reg+1) - 1) /
				(sample_div_reg + 1));
		/* setting usp mode 2 */
		len_val = ((1 << SIRFSOC_USP_MODE2_RXD_DELAY_OFFSET) |
				(1 << SIRFSOC_USP_MODE2_TXD_DELAY_OFFSET));
		len_val |= ((clk_div_reg & SIRFSOC_USP_MODE2_CLK_DIVISOR_MASK)
				<< SIRFSOC_USP_MODE2_CLK_DIVISOR_OFFSET);
		wr_regl(port, ureg->sirfsoc_mode2, len_val);
	}
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, set_baud, set_baud);
	/* set receive timeout && data bits len */
	rx_time_out = SIRFSOC_UART_RX_TIMEOUT(set_baud, 20000);
	rx_time_out = SIRFUART_RECV_TIMEOUT_VALUE(rx_time_out);
	txfifo_op_reg = rd_regl(port, ureg->sirfsoc_tx_fifo_op);
	wr_regl(port, ureg->sirfsoc_tx_fifo_op,
			(txfifo_op_reg & ~SIRFUART_FIFO_START));
	if (sirfport->uart_reg->uart_type == SIRF_REAL_UART) {
		config_reg |= SIRFUART_UART_RECV_TIMEOUT(rx_time_out);
		wr_regl(port, ureg->sirfsoc_line_ctrl, config_reg);
	} else {
		/*tx frame ctrl*/
		len_val = (data_bit_len - 1) << SIRFSOC_USP_TX_DATA_LEN_OFFSET;
		len_val |= (data_bit_len + 1 + stop_bit_len - 1) <<
				SIRFSOC_USP_TX_FRAME_LEN_OFFSET;
		len_val |= ((data_bit_len - 1) <<
				SIRFSOC_USP_TX_SHIFTER_LEN_OFFSET);
		len_val |= (((clk_div_reg & 0xc00) >> 10) <<
				SIRFSOC_USP_TX_CLK_DIVISOR_OFFSET);
		wr_regl(port, ureg->sirfsoc_tx_frame_ctrl, len_val);
		/*rx frame ctrl*/
		len_val = (data_bit_len - 1) << SIRFSOC_USP_RX_DATA_LEN_OFFSET;
		len_val |= (data_bit_len + 1 + stop_bit_len - 1) <<
				SIRFSOC_USP_RX_FRAME_LEN_OFFSET;
		len_val |= (data_bit_len - 1) <<
				SIRFSOC_USP_RX_SHIFTER_LEN_OFFSET;
		len_val |= (((clk_div_reg & 0xf000) >> 12) <<
				SIRFSOC_USP_RX_CLK_DIVISOR_OFFSET);
		wr_regl(port, ureg->sirfsoc_rx_frame_ctrl, len_val);
		/*async param*/
		wr_regl(port, ureg->sirfsoc_async_param_reg,
			(SIRFUART_USP_RECV_TIMEOUT(rx_time_out)) |
			(sample_div_reg & SIRFSOC_USP_ASYNC_DIV2_MASK) <<
			SIRFSOC_USP_ASYNC_DIV2_OFFSET);
	}
	if (sirfport->tx_dma_chan)
		wr_regl(port, ureg->sirfsoc_tx_dma_io_ctrl, SIRFUART_DMA_MODE);
	else
		wr_regl(port, ureg->sirfsoc_tx_dma_io_ctrl, SIRFUART_IO_MODE);
	if (sirfport->rx_dma_chan)
		wr_regl(port, ureg->sirfsoc_rx_dma_io_ctrl,
			rd_regl(port, ureg->sirfsoc_rx_dma_io_ctrl) &
			~SIRFUART_IO_MODE);
	else
		wr_regl(port, ureg->sirfsoc_rx_dma_io_ctrl,
			rd_regl(port, ureg->sirfsoc_rx_dma_io_ctrl) |
			SIRFUART_IO_MODE);
	sirfport->rx_period_time = 20000000;
	/* Reset Rx/Tx FIFO Threshold level for proper baudrate */
	if (set_baud < 1000000)
		threshold_div = 1;
	else
		threshold_div = 2;
	wr_regl(port, ureg->sirfsoc_tx_fifo_ctrl,
				SIRFUART_FIFO_THD(port) / threshold_div);
	wr_regl(port, ureg->sirfsoc_rx_fifo_ctrl,
				SIRFUART_FIFO_THD(port) / threshold_div);
	txfifo_op_reg |= SIRFUART_FIFO_START;
	wr_regl(port, ureg->sirfsoc_tx_fifo_op, txfifo_op_reg);
	uart_update_timeout(port, termios->c_cflag, set_baud);
	wr_regl(port, ureg->sirfsoc_tx_rx_en, SIRFUART_TX_EN | SIRFUART_RX_EN);
	spin_unlock_irqrestore(&port->lock, flags);
}