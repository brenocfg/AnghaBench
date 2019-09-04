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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fsi_master_acf {scalar_t__ sram; int /*<<< orphan*/  dev; scalar_t__ cvic; } ;

/* Variables and functions */
 scalar_t__ CMD_STAT_REG ; 
 scalar_t__ CVIC_TRIG_REG ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int ESHUTDOWN ; 
 int ETIMEDOUT ; 
 int STAT_COMPLETE ; 
#define  STAT_ERR_INVAL_CMD 130 
#define  STAT_ERR_INVAL_IRQ 129 
#define  STAT_ERR_MTOE 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  trace_fsi_master_acf_copro_command (struct fsi_master_acf*,int) ; 

__attribute__((used)) static int do_copro_command(struct fsi_master_acf *master, uint32_t op)
{
	uint32_t timeout = 10000000;
	uint8_t stat;

	trace_fsi_master_acf_copro_command(master, op);

	/* Send command */
	iowrite32be(op, master->sram + CMD_STAT_REG);

	/* Ring doorbell if any */
	if (master->cvic)
		iowrite32(0x2, master->cvic + CVIC_TRIG_REG);

	/* Wait for status to indicate completion (or error) */
	do {
		if (timeout-- == 0) {
			dev_warn(master->dev,
				 "Timeout waiting for coprocessor completion\n");
			return -ETIMEDOUT;
		}
		stat = ioread8(master->sram + CMD_STAT_REG);
	} while(stat < STAT_COMPLETE || stat == 0xff);

	if (stat == STAT_COMPLETE)
		return 0;
	switch(stat) {
	case STAT_ERR_INVAL_CMD:
		return -EINVAL;
	case STAT_ERR_INVAL_IRQ:
		return -EIO;
	case STAT_ERR_MTOE:
		return -ESHUTDOWN;
	}
	return -ENXIO;
}