#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ tx; } ;
struct mgsl_struct {int xmit_cnt; int x_char; int* xmit_buf; int xmit_tail; TYPE_1__ icount; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ CCAR ; 
 scalar_t__ DATAREG ; 
 int LSBONLY ; 
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  TCmd_SelectTicrTxFifostatus ; 
 int TDR ; 
 int /*<<< orphan*/  TICR ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_load_txfifo( struct mgsl_struct *info )
{
	int Fifocount;
	u8 TwoBytes[2];
	
	if ( !info->xmit_cnt && !info->x_char )
		return; 
		
	/* Select transmit FIFO status readback in TICR */
	usc_TCmd( info, TCmd_SelectTicrTxFifostatus );

	/* load the Transmit FIFO until FIFOs full or all data sent */

	while( (Fifocount = usc_InReg(info, TICR) >> 8) && info->xmit_cnt ) {
		/* there is more space in the transmit FIFO and */
		/* there is more data in transmit buffer */

		if ( (info->xmit_cnt > 1) && (Fifocount > 1) && !info->x_char ) {
 			/* write a 16-bit word from transmit buffer to 16C32 */
				
			TwoBytes[0] = info->xmit_buf[info->xmit_tail++];
			info->xmit_tail = info->xmit_tail & (SERIAL_XMIT_SIZE-1);
			TwoBytes[1] = info->xmit_buf[info->xmit_tail++];
			info->xmit_tail = info->xmit_tail & (SERIAL_XMIT_SIZE-1);
			
			outw( *((u16 *)TwoBytes), info->io_base + DATAREG);
				
			info->xmit_cnt -= 2;
			info->icount.tx += 2;
		} else {
			/* only 1 byte left to transmit or 1 FIFO slot left */
			
			outw( (inw( info->io_base + CCAR) & 0x0780) | (TDR+LSBONLY),
				info->io_base + CCAR );
			
			if (info->x_char) {
				/* transmit pending high priority char */
				outw( info->x_char,info->io_base + CCAR );
				info->x_char = 0;
			} else {
				outw( info->xmit_buf[info->xmit_tail++],info->io_base + CCAR );
				info->xmit_tail = info->xmit_tail & (SERIAL_XMIT_SIZE-1);
				info->xmit_cnt--;
			}
			info->icount.tx++;
		}
	}

}