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
struct img_i2c {int at_slave_event; int at_t_done; size_t at_cur_cmd; unsigned int line_status; int* seq; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned int const*) ; 
#define  CMD_GEN_DATA 137 
#define  CMD_GEN_START 136 
#define  CMD_GEN_STOP 135 
#define  CMD_RET_ACK 134 
#define  CMD_RET_DATA 133 
 int INT_SLAVE_EVENT ; 
 int INT_TRANSACTION_DONE ; 
 unsigned int ISR_COMPLETE (int /*<<< orphan*/ ) ; 
 unsigned int LINESTAT_ABORT_DET ; 
#define  LINESTAT_ACK_DET 132 
#define  LINESTAT_INPUT_HELD_V 131 
#define  LINESTAT_NACK_DET 130 
#define  LINESTAT_START_BIT_DET 129 
#define  LINESTAT_STOP_BIT_DET 128 
 int /*<<< orphan*/  SCB_OVERRIDE_REG ; 
 int /*<<< orphan*/  img_i2c_atomic_op (struct img_i2c*,int,int) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int img_i2c_sequence(struct img_i2c *i2c, u32 int_status)
{
	static const unsigned int continue_bits[] = {
		[CMD_GEN_START] = LINESTAT_START_BIT_DET,
		[CMD_GEN_DATA]  = LINESTAT_INPUT_HELD_V,
		[CMD_RET_ACK]   = LINESTAT_ACK_DET | LINESTAT_NACK_DET,
		[CMD_RET_DATA]  = LINESTAT_INPUT_HELD_V,
		[CMD_GEN_STOP]  = LINESTAT_STOP_BIT_DET,
	};
	int next_cmd = -1;
	u8 next_data = 0x00;

	if (int_status & INT_SLAVE_EVENT)
		i2c->at_slave_event = true;
	if (int_status & INT_TRANSACTION_DONE)
		i2c->at_t_done = true;

	if (!i2c->at_slave_event || !i2c->at_t_done)
		return 0;

	/* wait if no continue bits are set */
	if (i2c->at_cur_cmd >= 0 &&
	    i2c->at_cur_cmd < ARRAY_SIZE(continue_bits)) {
		unsigned int cont_bits = continue_bits[i2c->at_cur_cmd];

		if (cont_bits) {
			cont_bits |= LINESTAT_ABORT_DET;
			if (!(i2c->line_status & cont_bits))
				return 0;
		}
	}

	/* follow the sequence of commands in i2c->seq */
	next_cmd = *i2c->seq;
	/* stop on a nil */
	if (!next_cmd) {
		img_i2c_writel(i2c, SCB_OVERRIDE_REG, 0);
		return ISR_COMPLETE(0);
	}
	/* when generating data, the next byte is the data */
	if (next_cmd == CMD_GEN_DATA) {
		++i2c->seq;
		next_data = *i2c->seq;
	}
	++i2c->seq;
	img_i2c_atomic_op(i2c, next_cmd, next_data);

	return 0;
}