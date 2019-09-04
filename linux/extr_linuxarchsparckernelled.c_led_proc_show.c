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
 int AUXIO_LED ; 
 int get_auxio () ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int led_proc_show(struct seq_file *m, void *v)
{
	if (get_auxio() & AUXIO_LED)
		seq_puts(m, "on\n");
	else
		seq_puts(m, "off\n");
	return 0;
}