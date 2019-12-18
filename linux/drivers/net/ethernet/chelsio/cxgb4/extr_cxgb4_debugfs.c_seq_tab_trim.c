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
struct seq_tab {unsigned int rows; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int seq_tab_trim(struct seq_tab *p, unsigned int new_rows)
{
	if (new_rows > p->rows)
		return -EINVAL;
	p->rows = new_rows;
	return 0;
}