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
struct seq_file {struct hva_dev* private; } ;
struct hva_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hva_hw_dump_regs (struct hva_dev*,struct seq_file*) ; 

__attribute__((used)) static int regs_show(struct seq_file *s, void *data)
{
	struct hva_dev *hva = s->private;

	hva_hw_dump_regs(hva, s);

	return 0;
}