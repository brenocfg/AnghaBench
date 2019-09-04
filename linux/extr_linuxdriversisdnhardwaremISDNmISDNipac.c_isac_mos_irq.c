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
typedef  int /*<<< orphan*/  u8 ;
struct isac_hw {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAC_MOSR ; 
 int /*<<< orphan*/  ReadISAC (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isac_mos_irq(struct isac_hw *isac)
{
	u8 val;
	int ret;

	val = ReadISAC(isac, ISAC_MOSR);
	pr_debug("%s: ISAC MOSR %02x\n", isac->name, val);
#if ARCOFI_USE
	if (val & 0x08) {
		if (!isac->mon_rx) {
			isac->mon_rx = kmalloc(MAX_MON_FRAME, GFP_ATOMIC);
			if (!isac->mon_rx) {
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0xf0;
				isac->mocr |= 0x0a;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				goto afterMONR0;
			} else
				isac->mon_rxp = 0;
		}
		if (isac->mon_rxp >= MAX_MON_FRAME) {
			isac->mocr &= 0xf0;
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			goto afterMONR0;
		}
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR0);
		pr_debug("%s: ISAC MOR0 %02x\n", isac->name,
			 isac->mon_rx[isac->mon_rxp - 1]);
		if (isac->mon_rxp == 1) {
			isac->mocr |= 0x04;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
		}
	}
afterMONR0:
	if (val & 0x80) {
		if (!isac->mon_rx) {
			isac->mon_rx = kmalloc(MAX_MON_FRAME, GFP_ATOMIC);
			if (!isac->mon_rx) {
				pr_info("%s: ISAC MON RX out of memory!\n",
					isac->name);
				isac->mocr &= 0x0f;
				isac->mocr |= 0xa0;
				WriteISAC(isac, ISAC_MOCR, isac->mocr);
				goto afterMONR1;
			} else
				isac->mon_rxp = 0;
		}
		if (isac->mon_rxp >= MAX_MON_FRAME) {
			isac->mocr &= 0x0f;
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mon_rxp = 0;
			pr_debug("%s: ISAC MON RX overflow!\n", isac->name);
			goto afterMONR1;
		}
		isac->mon_rx[isac->mon_rxp++] = ReadISAC(isac, ISAC_MOR1);
		pr_debug("%s: ISAC MOR1 %02x\n", isac->name,
			 isac->mon_rx[isac->mon_rxp - 1]);
		isac->mocr |= 0x40;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
	}
afterMONR1:
	if (val & 0x04) {
		isac->mocr &= 0xf0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0x0a;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		if (isac->monitor) {
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_0,
					    isac->mon_rx, isac->mon_rxp);
			if (ret)
				kfree(isac->mon_rx);
		} else {
			pr_info("%s: MONITOR 0 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kfree(isac->mon_rx);
		}
		isac->mon_rx = NULL;
		isac->mon_rxp = 0;
	}
	if (val & 0x40) {
		isac->mocr &= 0x0f;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		isac->mocr |= 0xa0;
		WriteISAC(isac, ISAC_MOCR, isac->mocr);
		if (isac->monitor) {
			ret = isac->monitor(isac->dch.hw, MONITOR_RX_1,
					    isac->mon_rx, isac->mon_rxp);
			if (ret)
				kfree(isac->mon_rx);
		} else {
			pr_info("%s: MONITOR 1 received %d but no user\n",
				isac->name, isac->mon_rxp);
			kfree(isac->mon_rx);
		}
		isac->mon_rx = NULL;
		isac->mon_rxp = 0;
	}
	if (val & 0x02) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x08))) {
			isac->mocr &= 0xf0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0x0a;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitor)
					isac->monitor(isac->dch.hw,
						      MONITOR_TX_0, NULL, 0);
			}
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX0;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitor)
				isac->monitor(isac->dch.hw,
					      MONITOR_TX_0, NULL, 0);
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX0;
		}
		WriteISAC(isac, ISAC_MOX0, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX0\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	}
AfterMOX0:
	if (val & 0x20) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(val & 0x80))) {
			isac->mocr &= 0x0f;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			isac->mocr |= 0xa0;
			WriteISAC(isac, ISAC_MOCR, isac->mocr);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitor)
					isac->monitor(isac->dch.hw,
						      MONITOR_TX_1, NULL, 0);
			}
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX1;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitor)
				isac->monitor(isac->dch.hw,
					      MONITOR_TX_1, NULL, 0);
			kfree(isac->mon_tx);
			isac->mon_tx = NULL;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AfterMOX1;
		}
		WriteISAC(isac, ISAC_MOX1, isac->mon_tx[isac->mon_txp++]);
		pr_debug("%s: ISAC %02x -> MOX1\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	}
AfterMOX1:
	val = 0; /* dummy to avoid warning */
#endif
}