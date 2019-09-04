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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_SYS_CNTRCTRL ; 
 int /*<<< orphan*/  AU1000_SYS_TOYMATCH2 ; 
 int /*<<< orphan*/  AU1000_SYS_TOYREAD ; 
 int /*<<< orphan*/  AU1000_SYS_WAKEMSK ; 
 int /*<<< orphan*/  AU1000_SYS_WAKESRC ; 
 int BCSR_HEXCLEAR ; 
 int BCSR_INTCLR ; 
 size_t BCSR_INTSET ; 
 int BCSR_INTSTAT ; 
 int BCSR_MASKCLR ; 
 int BCSR_MASKSET ; 
 int BCSR_STATUS ; 
 int BCSR_SYSTEM ; 
 int BCSR_WHOAMI ; 
 scalar_t__ BCSR_WHOAMI_BOARD (int) ; 
 scalar_t__ BCSR_WHOAMI_DB1200 ; 
 int SYS_CNTRL_M20 ; 
 int /*<<< orphan*/  alchemy_gpio1_input_enable () ; 
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sleep () ; 
 void* bcsr_read (int) ; 
 int /*<<< orphan*/  bcsr_write (int,unsigned short) ; 
 scalar_t__ db1x_pm_sleep_secs ; 
 scalar_t__ db1x_pm_wakemsk ; 

__attribute__((used)) static int db1x_pm_enter(suspend_state_t state)
{
	unsigned short bcsrs[16];
	int i, j, hasint;

	/* save CPLD regs */
	hasint = bcsr_read(BCSR_WHOAMI);
	hasint = BCSR_WHOAMI_BOARD(hasint) >= BCSR_WHOAMI_DB1200;
	j = (hasint) ? BCSR_MASKSET : BCSR_SYSTEM;

	for (i = BCSR_STATUS; i <= j; i++)
		bcsrs[i] = bcsr_read(i);

	/* shut off hexleds */
	bcsr_write(BCSR_HEXCLEAR, 3);

	/* enable GPIO based wakeup */
	alchemy_gpio1_input_enable();

	/* clear and setup wake cause and source */
	alchemy_wrsys(0, AU1000_SYS_WAKEMSK);
	alchemy_wrsys(0, AU1000_SYS_WAKESRC);

	alchemy_wrsys(db1x_pm_wakemsk, AU1000_SYS_WAKEMSK);

	/* setup 1Hz-timer-based wakeup: wait for reg access */
	while (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M20)
		asm volatile ("nop");

	alchemy_wrsys(alchemy_rdsys(AU1000_SYS_TOYREAD) + db1x_pm_sleep_secs,
		      AU1000_SYS_TOYMATCH2);

	/* wait for value to really hit the register */
	while (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M20)
		asm volatile ("nop");

	/* ...and now the sandman can come! */
	au_sleep();


	/* restore CPLD regs */
	for (i = BCSR_STATUS; i <= BCSR_SYSTEM; i++)
		bcsr_write(i, bcsrs[i]);

	/* restore CPLD int registers */
	if (hasint) {
		bcsr_write(BCSR_INTCLR, 0xffff);
		bcsr_write(BCSR_MASKCLR, 0xffff);
		bcsr_write(BCSR_INTSTAT, 0xffff);
		bcsr_write(BCSR_INTSET, bcsrs[BCSR_INTSET]);
		bcsr_write(BCSR_MASKSET, bcsrs[BCSR_MASKSET]);
	}

	/* light up hexleds */
	bcsr_write(BCSR_HEXCLEAR, 0);

	return 0;
}