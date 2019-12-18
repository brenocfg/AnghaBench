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

/* Variables and functions */
 int CFG_AWG_ASYNC_EN ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hda_dbg_cfg(struct seq_file *s, int val)
{
	seq_puts(s, "\tAWG ");
	seq_puts(s, val & CFG_AWG_ASYNC_EN ? "enabled" : "disabled");
}