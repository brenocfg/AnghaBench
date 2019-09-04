#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ paddr; int /*<<< orphan*/  base; } ;
struct sti_cursor {TYPE_1__ pixmap; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cursor_dbg_pml(struct seq_file *s,
			   struct sti_cursor *cursor, u32 val)
{
	if (cursor->pixmap.paddr == val)
		seq_printf(s, "\tVirt @: %p", cursor->pixmap.base);
}