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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 

__attribute__((used)) static void npcm7xx_pin_dbg_show(struct pinctrl_dev *pctldev,
				 struct seq_file *s, unsigned int offset)
{
	seq_printf(s, "pinctrl_ops.dbg: %d", offset);
}