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
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  vsync_completion; int /*<<< orphan*/  lcdc; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long LDINTR_STATUS_MASK ; 
 unsigned long LDINTR_VEE ; 
 int /*<<< orphan*/  _LDINTR ; 
 unsigned long lcdc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_lcdc_wait_for_vsync(struct sh_mobile_lcdc_chan *ch)
{
	unsigned long ldintr;
	int ret;

	/* Enable VSync End interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	ldintr = lcdc_read(ch->lcdc, _LDINTR);
	ldintr |= LDINTR_VEE | LDINTR_STATUS_MASK;
	lcdc_write(ch->lcdc, _LDINTR, ldintr);

	ret = wait_for_completion_interruptible_timeout(&ch->vsync_completion,
							msecs_to_jiffies(100));
	if (!ret)
		return -ETIMEDOUT;

	return 0;
}