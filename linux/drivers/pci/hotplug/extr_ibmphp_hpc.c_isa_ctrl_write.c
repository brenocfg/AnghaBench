#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ io_start; } ;
struct TYPE_4__ {TYPE_1__ isa_ctlr; } ;
struct controller {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void isa_ctrl_write(struct controller *ctlr_ptr, u8 offset, u8 data)
{
	u16 start_address;
	u16 port_address;

	start_address = ctlr_ptr->u.isa_ctlr.io_start;
	port_address = start_address + (u16) offset;
	outb(data, port_address);
}