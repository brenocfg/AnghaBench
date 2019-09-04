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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int addr; int /*<<< orphan*/  cip; } ;
struct TYPE_4__ {TYPE_1__ hfc; } ;
struct IsdnCardState {int debug; TYPE_2__ hw; } ;

/* Variables and functions */
 int L1_DEB_HSCX_FIFO ; 
 int /*<<< orphan*/  byteout (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WriteHFC(struct IsdnCardState *cs, int data, u_char reg, u_char value)
{
	byteout(cs->hw.hfc.addr | 1, reg);
	cs->hw.hfc.cip = reg;
	if (data)
		byteout(cs->hw.hfc.addr, value);
	if (cs->debug & L1_DEB_HSCX_FIFO && (data != 2))
		debugl1(cs, "hfc W%c %02x %02x", data ? 'D' : 'C', reg, value);
}