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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct hermes {TYPE_1__* ops; scalar_t__ eeprom_pda; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int (* cmd_wait ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HERMES_AUXDATA ; 
 int /*<<< orphan*/  HERMES_CMD_READMIF ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int hermes_aux_control (struct hermes*,int) ; 
 int /*<<< orphan*/  hermes_aux_setaddr (struct hermes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_read_words (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hermes_read_pda(struct hermes *hw, __le16 *pda, u32 pda_addr,
			   u16 pda_len)
{
	int ret;
	u16 pda_size;
	u16 data_len = pda_len;
	__le16 *data = pda;

	if (hw->eeprom_pda) {
		/* PDA of spectrum symbol is in eeprom */

		/* Issue command to read EEPROM */
		ret = hw->ops->cmd_wait(hw, HERMES_CMD_READMIF, 0, NULL);
		if (ret)
			return ret;
	} else {
		/* wl_lkm does not include PDA size in the PDA area.
		 * We will pad the information into pda, so other routines
		 * don't have to be modified */
		pda[0] = cpu_to_le16(pda_len - 2);
			/* Includes CFG_PROD_DATA but not itself */
		pda[1] = cpu_to_le16(0x0800); /* CFG_PROD_DATA */
		data_len = pda_len - 4;
		data = pda + 2;
	}

	/* Open auxiliary port */
	ret = hermes_aux_control(hw, 1);
	pr_debug("AUX enable returned %d\n", ret);
	if (ret)
		return ret;

	/* Read PDA */
	hermes_aux_setaddr(hw, pda_addr);
	hermes_read_words(hw, HERMES_AUXDATA, data, data_len / 2);

	/* Close aux port */
	ret = hermes_aux_control(hw, 0);
	pr_debug("AUX disable returned %d\n", ret);

	/* Check PDA length */
	pda_size = le16_to_cpu(pda[0]);
	pr_debug("Actual PDA length %d, Max allowed %d\n",
		 pda_size, pda_len);
	if (pda_size > pda_len)
		return -EINVAL;

	return 0;
}