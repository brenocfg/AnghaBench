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
struct TYPE_3__ {scalar_t__ isac; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ avm; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ AVM_HDLC_1 ; 
 scalar_t__ AVM_HDLC_2 ; 
 scalar_t__ inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u_char
ReadHDLCPnP(struct IsdnCardState *cs, int chan, u_char offset)
{
	register u_char idx = chan ? AVM_HDLC_2 : AVM_HDLC_1;
	register u_char val;

	outb(idx, cs->hw.avm.cfg_reg + 4);
	val = inb(cs->hw.avm.isac + offset);
	return (val);
}