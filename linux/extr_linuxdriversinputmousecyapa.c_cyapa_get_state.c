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
typedef  void* u8 ;
struct cyapa {scalar_t__ state; scalar_t__ gen; void** status; scalar_t__ smbus; TYPE_1__* client; } ;
struct TYPE_6__ {int (* state_parse ) (struct cyapa*,void**,int) ;} ;
struct TYPE_5__ {int (* state_parse ) (struct cyapa*,void**,int) ;} ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_HEAD_OFFSET ; 
 int BL_STATUS_SIZE ; 
 int /*<<< orphan*/  CYAPA_CMD_BL_STATUS ; 
 scalar_t__ CYAPA_GEN3 ; 
 scalar_t__ CYAPA_GEN5 ; 
 scalar_t__ CYAPA_GEN6 ; 
 scalar_t__ CYAPA_GEN_UNKNOWN ; 
 scalar_t__ CYAPA_STATE_BL_BUSY ; 
 scalar_t__ CYAPA_STATE_NO_DEVICE ; 
 int EAGAIN ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 size_t REG_BL_ERROR ; 
 size_t REG_BL_STATUS ; 
 size_t REG_OP_STATUS ; 
 TYPE_3__ cyapa_gen3_ops ; 
 TYPE_2__ cyapa_gen5_ops ; 
 int cyapa_i2c_read (struct cyapa*,int /*<<< orphan*/ ,int,void**) ; 
 int cyapa_i2c_reg_read_block (struct cyapa*,int /*<<< orphan*/ ,int,void**) ; 
 int cyapa_i2c_write (struct cyapa*,int /*<<< orphan*/ ,int,void**) ; 
 int cyapa_pip_state_parse (struct cyapa*,void**,int) ; 
 int cyapa_read_block (struct cyapa*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct cyapa*,void**,int) ; 
 int stub2 (struct cyapa*,void**,int) ; 

__attribute__((used)) static int cyapa_get_state(struct cyapa *cyapa)
{
	u8 status[BL_STATUS_SIZE];
	u8 cmd[32];
	/* The i2c address of gen4 and gen5 trackpad device must be even. */
	bool even_addr = ((cyapa->client->addr & 0x0001) == 0);
	bool smbus = false;
	int retries = 2;
	int error;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/*
	 * Get trackpad status by reading 3 registers starting from 0.
	 * If the device is in the bootloader, this will be BL_HEAD.
	 * If the device is in operation mode, this will be the DATA regs.
	 *
	 */
	error = cyapa_i2c_reg_read_block(cyapa, BL_HEAD_OFFSET, BL_STATUS_SIZE,
				       status);

	/*
	 * On smbus systems in OP mode, the i2c_reg_read will fail with
	 * -ETIMEDOUT.  In this case, try again using the smbus equivalent
	 * command.  This should return a BL_HEAD indicating CYAPA_STATE_OP.
	 */
	if (cyapa->smbus && (error == -ETIMEDOUT || error == -ENXIO)) {
		if (!even_addr)
			error = cyapa_read_block(cyapa,
					CYAPA_CMD_BL_STATUS, status);
		smbus = true;
	}

	if (error != BL_STATUS_SIZE)
		goto error;

	/*
	 * Detect trackpad protocol based on characteristic registers and bits.
	 */
	do {
		cyapa->status[REG_OP_STATUS] = status[REG_OP_STATUS];
		cyapa->status[REG_BL_STATUS] = status[REG_BL_STATUS];
		cyapa->status[REG_BL_ERROR] = status[REG_BL_ERROR];

		if (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN3) {
			error = cyapa_gen3_ops.state_parse(cyapa,
					status, BL_STATUS_SIZE);
			if (!error)
				goto out_detected;
		}
		if (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN6 ||
				cyapa->gen == CYAPA_GEN5) {
			error = cyapa_pip_state_parse(cyapa,
					status, BL_STATUS_SIZE);
			if (!error)
				goto out_detected;
		}
		/* For old Gen5 trackpads detecting. */
		if ((cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN5) &&
			!smbus && even_addr) {
			error = cyapa_gen5_ops.state_parse(cyapa,
					status, BL_STATUS_SIZE);
			if (!error)
				goto out_detected;
		}

		/*
		 * Write 0x00 0x00 to trackpad device to force update its
		 * status, then redo the detection again.
		 */
		if (!smbus) {
			cmd[0] = 0x00;
			cmd[1] = 0x00;
			error = cyapa_i2c_write(cyapa, 0, 2, cmd);
			if (error)
				goto error;

			msleep(50);

			error = cyapa_i2c_read(cyapa, BL_HEAD_OFFSET,
					BL_STATUS_SIZE, status);
			if (error)
				goto error;
		}
	} while (--retries > 0 && !smbus);

	goto error;

out_detected:
	if (cyapa->state <= CYAPA_STATE_BL_BUSY)
		return -EAGAIN;
	return 0;

error:
	return (error < 0) ? error : -EAGAIN;
}