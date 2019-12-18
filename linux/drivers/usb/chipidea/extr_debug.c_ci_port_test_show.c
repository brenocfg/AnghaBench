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
struct seq_file {struct ci_hdrc* private; } ;
struct ci_hdrc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int hw_port_test_get (struct ci_hdrc*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ci_port_test_show(struct seq_file *s, void *data)
{
	struct ci_hdrc *ci = s->private;
	unsigned long flags;
	unsigned mode;

	pm_runtime_get_sync(ci->dev);
	spin_lock_irqsave(&ci->lock, flags);
	mode = hw_port_test_get(ci);
	spin_unlock_irqrestore(&ci->lock, flags);
	pm_runtime_put_sync(ci->dev);

	seq_printf(s, "mode = %u\n", mode);

	return 0;
}