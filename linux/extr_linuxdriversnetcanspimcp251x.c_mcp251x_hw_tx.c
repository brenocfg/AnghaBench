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
typedef  int u32 ;
struct spi_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  spi; int /*<<< orphan*/ * spi_tx_buf; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int DLC_RTR_SHIFT ; 
 int GET_BYTE (int,int) ; 
 int INSTRUCTION_LOAD_TXB (int) ; 
 int /*<<< orphan*/  INSTRUCTION_RTS (int) ; 
 int SIDH_SHIFT ; 
 int SIDL_EID_MASK ; 
 int SIDL_EID_SHIFT ; 
 int SIDL_EXIDE_SHIFT ; 
 int SIDL_SID_MASK ; 
 int SIDL_SID_SHIFT ; 
 int SPI_TRANSFER_BUF_LEN ; 
 size_t TXBCTRL_OFF ; 
 int TXBDAT_OFF ; 
 size_t TXBDLC_OFF ; 
 size_t TXBEID0_OFF ; 
 size_t TXBEID8_OFF ; 
 size_t TXBSIDH_OFF ; 
 size_t TXBSIDL_OFF ; 
 int /*<<< orphan*/  mcp251x_hw_tx_frame (struct spi_device*,int*,int,int) ; 
 int /*<<< orphan*/  mcp251x_spi_trans (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void mcp251x_hw_tx(struct spi_device *spi, struct can_frame *frame,
			  int tx_buf_idx)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);
	u32 sid, eid, exide, rtr;
	u8 buf[SPI_TRANSFER_BUF_LEN];

	exide = (frame->can_id & CAN_EFF_FLAG) ? 1 : 0; /* Extended ID Enable */
	if (exide)
		sid = (frame->can_id & CAN_EFF_MASK) >> 18;
	else
		sid = frame->can_id & CAN_SFF_MASK; /* Standard ID */
	eid = frame->can_id & CAN_EFF_MASK; /* Extended ID */
	rtr = (frame->can_id & CAN_RTR_FLAG) ? 1 : 0; /* Remote transmission */

	buf[TXBCTRL_OFF] = INSTRUCTION_LOAD_TXB(tx_buf_idx);
	buf[TXBSIDH_OFF] = sid >> SIDH_SHIFT;
	buf[TXBSIDL_OFF] = ((sid & SIDL_SID_MASK) << SIDL_SID_SHIFT) |
		(exide << SIDL_EXIDE_SHIFT) |
		((eid >> SIDL_EID_SHIFT) & SIDL_EID_MASK);
	buf[TXBEID8_OFF] = GET_BYTE(eid, 1);
	buf[TXBEID0_OFF] = GET_BYTE(eid, 0);
	buf[TXBDLC_OFF] = (rtr << DLC_RTR_SHIFT) | frame->can_dlc;
	memcpy(buf + TXBDAT_OFF, frame->data, frame->can_dlc);
	mcp251x_hw_tx_frame(spi, buf, frame->can_dlc, tx_buf_idx);

	/* use INSTRUCTION_RTS, to avoid "repeated frame problem" */
	priv->spi_tx_buf[0] = INSTRUCTION_RTS(1 << tx_buf_idx);
	mcp251x_spi_trans(priv->spi, 1);
}