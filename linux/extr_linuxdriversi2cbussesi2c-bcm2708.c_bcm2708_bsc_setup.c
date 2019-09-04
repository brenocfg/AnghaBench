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
typedef  int u32 ;
struct bcm2708_i2c {int cdiv; int clk_tout; int nmsgs; int pos; TYPE_1__* msg; } ;
struct TYPE_2__ {int flags; int addr; int len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSC_A ; 
 int /*<<< orphan*/  BSC_C ; 
 int /*<<< orphan*/  BSC_CLKT ; 
 int BSC_C_CLEAR_1 ; 
 int BSC_C_I2CEN ; 
 int BSC_C_INTD ; 
 int BSC_C_INTR ; 
 int BSC_C_INTT ; 
 int BSC_C_READ ; 
 int BSC_C_ST ; 
 int /*<<< orphan*/  BSC_DIV ; 
 int /*<<< orphan*/  BSC_DLEN ; 
 int /*<<< orphan*/  BSC_FIFO ; 
 int /*<<< orphan*/  BSC_S ; 
 int BSC_S_CLKT ; 
 int BSC_S_DONE ; 
 int BSC_S_ERR ; 
 int BSC_S_TA ; 
 int I2C_M_RD ; 
 int I2C_WAIT_LOOP_COUNT ; 
 int bcm2708_rd (struct bcm2708_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2708_wr (struct bcm2708_i2c*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ combined ; 

__attribute__((used)) static inline int bcm2708_bsc_setup(struct bcm2708_i2c *bi)
{
	u32 cdiv, s, clk_tout;
	u32 c = BSC_C_I2CEN | BSC_C_INTD | BSC_C_ST | BSC_C_CLEAR_1;
	int wait_loops = I2C_WAIT_LOOP_COUNT;

	/* Can't call clk_get_rate as it locks a mutex and here we are spinlocked.
	 * Use the value that we cached in the probe.
	 */
	cdiv = bi->cdiv;
	clk_tout = bi->clk_tout;

	if (bi->msg->flags & I2C_M_RD)
		c |= BSC_C_INTR | BSC_C_READ;
	else
		c |= BSC_C_INTT;

	bcm2708_wr(bi, BSC_CLKT, clk_tout);
	bcm2708_wr(bi, BSC_DIV, cdiv);
	bcm2708_wr(bi, BSC_A, bi->msg->addr);
	bcm2708_wr(bi, BSC_DLEN, bi->msg->len);
	if (combined)
	{
		/* Do the next two messages meet combined transaction criteria?
		   - Current message is a write, next message is a read
		   - Both messages to same slave address
		   - Write message can fit inside FIFO (16 bytes or less) */
		if ( (bi->nmsgs > 1) &&
			!(bi->msg[0].flags & I2C_M_RD) && (bi->msg[1].flags & I2C_M_RD) &&
			 (bi->msg[0].addr == bi->msg[1].addr) && (bi->msg[0].len <= 16)) {

			/* Clear FIFO */
			bcm2708_wr(bi, BSC_C, BSC_C_CLEAR_1);

			/* Fill FIFO with entire write message (16 byte FIFO) */
			while (bi->pos < bi->msg->len) {
				bcm2708_wr(bi, BSC_FIFO, bi->msg->buf[bi->pos++]);
			}
			/* Start write transfer (no interrupts, don't clear FIFO) */
			bcm2708_wr(bi, BSC_C, BSC_C_I2CEN | BSC_C_ST);

			/* poll for transfer start bit (should only take 1-20 polls) */
			do {
				s = bcm2708_rd(bi, BSC_S);
			} while (!(s & (BSC_S_TA | BSC_S_ERR | BSC_S_CLKT | BSC_S_DONE)) && --wait_loops >= 0);

			/* did we time out or some error occured? */
			if (wait_loops < 0 || (s & (BSC_S_ERR | BSC_S_CLKT))) {
				return -1;
			}

			/* Send next read message before the write transfer finishes. */
			bi->nmsgs--;
			bi->msg++;
			bi->pos = 0;
			bcm2708_wr(bi, BSC_DLEN, bi->msg->len);
			c = BSC_C_I2CEN | BSC_C_INTD | BSC_C_INTR | BSC_C_ST | BSC_C_READ;
		}
	}
	bcm2708_wr(bi, BSC_C, c);

	return 0;
}