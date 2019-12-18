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
typedef  int /*<<< orphan*/  mace_private ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MACE_BIUCC ; 
 int /*<<< orphan*/  MACE_FIFOCC ; 
 int /*<<< orphan*/  MACE_IAC ; 
 int MACE_IAC_ADDRCHG ; 
 int MACE_IAC_PHYADDR ; 
 int /*<<< orphan*/  MACE_IMR ; 
 int /*<<< orphan*/  MACE_MACCC ; 
 int /*<<< orphan*/  MACE_PADR ; 
 int /*<<< orphan*/  MACE_PHYCC ; 
 int /*<<< orphan*/  MACE_PLSCC ; 
 int /*<<< orphan*/  MACE_RCVFC ; 
 int if_port ; 
 int mace_read (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mace_write (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mace_init(mace_private *lp, unsigned int ioaddr, char *enet_addr)
{
  int i;
  int ct = 0;

  /* MACE Software reset */
  mace_write(lp, ioaddr, MACE_BIUCC, 1);
  while (mace_read(lp, ioaddr, MACE_BIUCC) & 0x01) {
    /* Wait for reset bit to be cleared automatically after <= 200ns */;
    if(++ct > 500)
    {
	pr_err("reset failed, card removed?\n");
    	return -1;
    }
    udelay(1);
  }
  mace_write(lp, ioaddr, MACE_BIUCC, 0);

  /* The Am2150 requires that the MACE FIFOs operate in burst mode. */
  mace_write(lp, ioaddr, MACE_FIFOCC, 0x0F);

  mace_write(lp,ioaddr, MACE_RCVFC, 0); /* Disable Auto Strip Receive */
  mace_write(lp, ioaddr, MACE_IMR, 0xFF); /* Disable all interrupts until _open */

  /*
   * Bit 2-1 PORTSEL[1-0] Port Select.
   * 00 AUI/10Base-2
   * 01 10Base-T
   * 10 DAI Port (reserved in Am2150)
   * 11 GPSI
   * For this card, only the first two are valid.
   * So, PLSCC should be set to
   * 0x00 for 10Base-2
   * 0x02 for 10Base-T
   * Or just set ASEL in PHYCC below!
   */
  switch (if_port) {
    case 1:
      mace_write(lp, ioaddr, MACE_PLSCC, 0x02);
      break;
    case 2:
      mace_write(lp, ioaddr, MACE_PLSCC, 0x00);
      break;
    default:
      mace_write(lp, ioaddr, MACE_PHYCC, /* ASEL */ 4);
      /* ASEL Auto Select.  When set, the PORTSEL[1-0] bits are overridden,
	 and the MACE device will automatically select the operating media
	 interface port. */
      break;
  }

  mace_write(lp, ioaddr, MACE_IAC, MACE_IAC_ADDRCHG | MACE_IAC_PHYADDR);
  /* Poll ADDRCHG bit */
  ct = 0;
  while (mace_read(lp, ioaddr, MACE_IAC) & MACE_IAC_ADDRCHG)
  {
  	if(++ ct > 500)
  	{
		pr_err("ADDRCHG timeout, card removed?\n");
  		return -1;
  	}
  }
  /* Set PADR register */
  for (i = 0; i < ETH_ALEN; i++)
    mace_write(lp, ioaddr, MACE_PADR, enet_addr[i]);

  /* MAC Configuration Control Register should be written last */
  /* Let set_multicast_list set this. */
  /* mace_write(lp, ioaddr, MACE_MACCC, MACE_MACCC_ENXMT | MACE_MACCC_ENRCV); */
  mace_write(lp, ioaddr, MACE_MACCC, 0x00);
  return 0;
}