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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_ADDR_MASK_ ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_CMD_EWEN_ ; 
 int E2P_CMD_EPC_CMD_WRITE_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int lan743x_eeprom_confirm_not_busy (struct lan743x_adapter*) ; 
 int lan743x_eeprom_wait (struct lan743x_adapter*) ; 

__attribute__((used)) static int lan743x_eeprom_write(struct lan743x_adapter *adapter,
				u32 offset, u32 length, u8 *data)
{
	int retval;
	u32 val;
	int i;

	retval = lan743x_eeprom_confirm_not_busy(adapter);
	if (retval)
		return retval;

	/* Issue write/erase enable command */
	val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_EWEN_;
	lan743x_csr_write(adapter, E2P_CMD, val);

	retval = lan743x_eeprom_wait(adapter);
	if (retval < 0)
		return retval;

	for (i = 0; i < length; i++) {
		/* Fill data register */
		val = data[i];
		lan743x_csr_write(adapter, E2P_DATA, val);

		/* Send "write" command */
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_WRITE_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		lan743x_csr_write(adapter, E2P_CMD, val);

		retval = lan743x_eeprom_wait(adapter);
		if (retval < 0)
			return retval;

		offset++;
	}

	return 0;
}