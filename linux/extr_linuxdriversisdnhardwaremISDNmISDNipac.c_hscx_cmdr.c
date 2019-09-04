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
typedef  int /*<<< orphan*/  u8 ;
struct hscx_hw {TYPE_1__* ip; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPACX_CMDRB ; 
 int /*<<< orphan*/  IPAC_CMDRB ; 
 int IPAC_TYPE_IPACX ; 
 int /*<<< orphan*/  WriteHSCX (struct hscx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitforCEC (struct hscx_hw*) ; 

__attribute__((used)) static void
hscx_cmdr(struct hscx_hw *hx, u8 cmd)
{
	if (hx->ip->type & IPAC_TYPE_IPACX)
		WriteHSCX(hx, IPACX_CMDRB, cmd);
	else {
		waitforCEC(hx);
		WriteHSCX(hx, IPAC_CMDRB, cmd);
	}
}