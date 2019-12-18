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
struct TYPE_2__ {scalar_t__ lpm; } ;
struct ci_hdrc {TYPE_1__ hw_bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLC_PSPD ; 
 int /*<<< orphan*/  OP_DEVLC ; 
 int /*<<< orphan*/  OP_PORTSC ; 
 int /*<<< orphan*/  PORTSC_HSP ; 
 int hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_port_is_high_speed(struct ci_hdrc *ci)
{
	return ci->hw_bank.lpm ? hw_read(ci, OP_DEVLC, DEVLC_PSPD) :
		hw_read(ci, OP_PORTSC, PORTSC_HSP);
}