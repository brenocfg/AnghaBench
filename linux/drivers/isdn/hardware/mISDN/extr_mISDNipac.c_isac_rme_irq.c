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
struct TYPE_2__ {int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  err_crc; int /*<<< orphan*/  err_rx; } ;
struct isac_hw {TYPE_1__ dch; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_RBCL ; 
 int /*<<< orphan*/  ISAC_RSTA ; 
 int ReadISAC (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac_hw*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_Dchannel (TYPE_1__*) ; 

__attribute__((used)) static void
isac_rme_irq(struct isac_hw *isac)
{
	u8 val, count;

	val = ReadISAC(isac, ISAC_RSTA);
	if ((val & 0x70) != 0x20) {
		if (val & 0x40) {
			pr_debug("%s: ISAC RDO\n", isac->name);
#ifdef ERROR_STATISTIC
			isac->dch.err_rx++;
#endif
		}
		if (!(val & 0x20)) {
			pr_debug("%s: ISAC CRC error\n", isac->name);
#ifdef ERROR_STATISTIC
			isac->dch.err_crc++;
#endif
		}
		WriteISAC(isac, ISAC_CMDR, 0x80);
		dev_kfree_skb(isac->dch.rx_skb);
		isac->dch.rx_skb = NULL;
	} else {
		count = ReadISAC(isac, ISAC_RBCL) & 0x1f;
		if (count == 0)
			count = 32;
		isac_empty_fifo(isac, count);
		recv_Dchannel(&isac->dch);
	}
}