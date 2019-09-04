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
struct TYPE_3__ {int /*<<< orphan*/  hscx; int /*<<< orphan*/  adr; } ;
struct TYPE_4__ {TYPE_1__ mic; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u_char
ReadHSCX(struct IsdnCardState *cs, int hscx, u_char offset)
{
	return (readreg(cs->hw.mic.adr,
			cs->hw.mic.hscx, offset + (hscx ? 0x40 : 0)));
}