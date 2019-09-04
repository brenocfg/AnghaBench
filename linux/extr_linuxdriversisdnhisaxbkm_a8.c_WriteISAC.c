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
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  data_adr; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ ax; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
WriteISAC(struct IsdnCardState *cs, u_char offset, u_char value)
{
	writereg(cs->hw.ax.base, cs->hw.ax.data_adr, offset | 0x80, value);
}