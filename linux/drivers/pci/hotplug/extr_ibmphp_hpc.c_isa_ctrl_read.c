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
struct TYPE_3__ {scalar_t__ io_end; scalar_t__ io_start; } ;
struct TYPE_4__ {TYPE_1__ isa_ctlr; } ;
struct controller {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ inb (scalar_t__) ; 

__attribute__((used)) static u8 isa_ctrl_read(struct controller *ctlr_ptr, u8 offset)
{
	u16 start_address;
	u16 end_address;
	u8 data;

	start_address = ctlr_ptr->u.isa_ctlr.io_start;
	end_address = ctlr_ptr->u.isa_ctlr.io_end;
	data = inb(start_address + offset);
	return data;
}