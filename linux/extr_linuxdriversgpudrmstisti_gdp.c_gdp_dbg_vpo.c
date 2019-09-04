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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 

__attribute__((used)) static void gdp_dbg_vpo(struct seq_file *s, int val)
{
	seq_printf(s, "\txdo:%4d\tydo:%4d", val & 0xFFFF, (val >> 16) & 0xFFFF);
}