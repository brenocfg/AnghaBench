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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int* CSR_SA110_CNTL ; 
 scalar_t__* CSR_TIMER4_CLR ; 
 int* CSR_TIMER4_CNTL ; 
 int EBUSY ; 
 int /*<<< orphan*/  IRQ_TIMER4 ; 
 int TIMER_CNTL_AUTORELOAD ; 
 int TIMER_CNTL_DIV256 ; 
 int TIMER_CNTL_ENABLE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int mem_fclk_21285 ; 
 int reload ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int soft_margin ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_alive ; 
 int /*<<< orphan*/  watchdog_fire ; 
 int /*<<< orphan*/  watchdog_ping () ; 

__attribute__((used)) static int watchdog_open(struct inode *inode, struct file *file)
{
	int ret;

	if (*CSR_SA110_CNTL & (1 << 13))
		return -EBUSY;

	if (test_and_set_bit(1, &timer_alive))
		return -EBUSY;

	reload = soft_margin * (mem_fclk_21285 / 256);

	*CSR_TIMER4_CLR = 0;
	watchdog_ping();
	*CSR_TIMER4_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_AUTORELOAD
		| TIMER_CNTL_DIV256;

#ifdef ONLY_TESTING
	ret = request_irq(IRQ_TIMER4, watchdog_fire, 0, "watchdog", NULL);
	if (ret) {
		*CSR_TIMER4_CNTL = 0;
		clear_bit(1, &timer_alive);
	}
#else
	/*
	 * Setting this bit is irreversible; once enabled, there is
	 * no way to disable the watchdog.
	 */
	*CSR_SA110_CNTL |= 1 << 13;

	ret = 0;
#endif
	stream_open(inode, file);
	return ret;
}