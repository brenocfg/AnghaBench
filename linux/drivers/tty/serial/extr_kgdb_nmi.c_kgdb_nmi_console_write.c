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
typedef  int uint ;
struct console {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_char ) (char const) ;} ;

/* Variables and functions */
 TYPE_1__* dbg_io_ops ; 
 int /*<<< orphan*/  stub1 (char const) ; 

__attribute__((used)) static void kgdb_nmi_console_write(struct console *co, const char *s, uint c)
{
	int i;

	for (i = 0; i < c; i++)
		dbg_io_ops->write_char(s[i]);
}