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
typedef  scalar_t__ u_char ;
struct TYPE_3__ {scalar_t__ iobase; } ;
struct TYPE_4__ {TYPE_1__ w6692; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
WriteW6692(struct IsdnCardState *cs, u_char offset, u_char value)
{
	outb(value, cs->hw.w6692.iobase + offset);
}