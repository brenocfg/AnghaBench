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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_hwif {int dummy; } ;
struct hinic_api_cmd_chain {int /*<<< orphan*/  chain_type; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_CMD_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HINIC_API_CMD_CHAIN_REQ_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_API_CMD_CHAIN_REQ_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_API_CMD_CHAIN_REQ_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_CSR_API_CMD_CHAIN_REQ_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESTART ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int api_cmd_hw_restart(struct hinic_api_cmd_chain *chain)
{
	struct hinic_hwif *hwif = chain->hwif;
	int err = -ETIMEDOUT;
	unsigned long end;
	u32 reg_addr, val;

	/* Read Modify Write */
	reg_addr = HINIC_CSR_API_CMD_CHAIN_REQ_ADDR(chain->chain_type);
	val = hinic_hwif_read_reg(hwif, reg_addr);

	val = HINIC_API_CMD_CHAIN_REQ_CLEAR(val, RESTART);
	val |= HINIC_API_CMD_CHAIN_REQ_SET(1, RESTART);

	hinic_hwif_write_reg(hwif, reg_addr, val);

	end = jiffies + msecs_to_jiffies(API_CMD_TIMEOUT);
	do {
		val = hinic_hwif_read_reg(hwif, reg_addr);

		if (!HINIC_API_CMD_CHAIN_REQ_GET(val, RESTART)) {
			err = 0;
			break;
		}

		msleep(20);
	} while (time_before(jiffies, end));

	return err;
}