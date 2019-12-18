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
struct seq_file {struct musb* private; } ;
struct musb {int /*<<< orphan*/  controller; int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_TESTMODE ; 
 unsigned int MUSB_TEST_FIFO_ACCESS ; 
 unsigned int MUSB_TEST_FORCE_FS ; 
 unsigned int MUSB_TEST_FORCE_HOST ; 
 unsigned int MUSB_TEST_FORCE_HS ; 
 unsigned int MUSB_TEST_J ; 
 unsigned int MUSB_TEST_K ; 
 unsigned int MUSB_TEST_PACKET ; 
 unsigned int MUSB_TEST_SE0_NAK ; 
 unsigned int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static int musb_test_mode_show(struct seq_file *s, void *unused)
{
	struct musb		*musb = s->private;
	unsigned		test;

	pm_runtime_get_sync(musb->controller);
	test = musb_readb(musb->mregs, MUSB_TESTMODE);
	pm_runtime_mark_last_busy(musb->controller);
	pm_runtime_put_autosuspend(musb->controller);

	if (test == (MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_FS))
		seq_printf(s, "force host full-speed\n");

	else if (test == (MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_HS))
		seq_printf(s, "force host high-speed\n");

	else if (test == MUSB_TEST_FORCE_HOST)
		seq_printf(s, "force host\n");

	else if (test == MUSB_TEST_FIFO_ACCESS)
		seq_printf(s, "fifo access\n");

	else if (test == MUSB_TEST_FORCE_FS)
		seq_printf(s, "force full-speed\n");

	else if (test == MUSB_TEST_FORCE_HS)
		seq_printf(s, "force high-speed\n");

	else if (test == MUSB_TEST_PACKET)
		seq_printf(s, "test packet\n");

	else if (test == MUSB_TEST_K)
		seq_printf(s, "test K\n");

	else if (test == MUSB_TEST_J)
		seq_printf(s, "test J\n");

	else if (test == MUSB_TEST_SE0_NAK)
		seq_printf(s, "test SE0 NAK\n");

	return 0;
}