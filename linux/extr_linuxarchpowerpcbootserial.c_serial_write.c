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
struct serial_console_data {int /*<<< orphan*/  (* putc ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct serial_console_data* data; } ;

/* Variables and functions */
 TYPE_1__ console_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_write(const char *buf, int len)
{
	struct serial_console_data *scdp = console_ops.data;

	while (*buf != '\0')
		scdp->putc(*buf++);
}