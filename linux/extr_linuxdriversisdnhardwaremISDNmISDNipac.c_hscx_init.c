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
typedef  int u8 ;
struct TYPE_3__ {int debug; } ;
struct hscx_hw {TYPE_2__* ip; TYPE_1__ bch; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int /*<<< orphan*/ * HSCXVer ; 
 int /*<<< orphan*/  HSCX_VSTR ; 
 int /*<<< orphan*/  IPAC_CCR1 ; 
 int /*<<< orphan*/  IPAC_CCR2 ; 
 int /*<<< orphan*/  IPAC_RAH2 ; 
 int /*<<< orphan*/  IPAC_RCCR ; 
 int /*<<< orphan*/  IPAC_RLCR ; 
 int IPAC_TYPE_HSCX ; 
 int /*<<< orphan*/  IPAC_XBCH ; 
 int /*<<< orphan*/  IPAC_XCCR ; 
 int ReadHSCX (struct hscx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteHSCX (struct hscx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hscx_init(struct hscx_hw *hx)
{
	u8 val;

	WriteHSCX(hx, IPAC_RAH2, 0xFF);
	WriteHSCX(hx, IPAC_XBCH, 0x00);
	WriteHSCX(hx, IPAC_RLCR, 0x00);

	if (hx->ip->type & IPAC_TYPE_HSCX) {
		WriteHSCX(hx, IPAC_CCR1, 0x85);
		val = ReadHSCX(hx, HSCX_VSTR);
		pr_debug("%s: HSCX VSTR %02x\n", hx->ip->name, val);
		if (hx->bch.debug & DEBUG_HW)
			pr_notice("%s: HSCX version %s\n", hx->ip->name,
				  HSCXVer[val & 0x0f]);
	} else
		WriteHSCX(hx, IPAC_CCR1, 0x82);
	WriteHSCX(hx, IPAC_CCR2, 0x30);
	WriteHSCX(hx, IPAC_XCCR, 0x07);
	WriteHSCX(hx, IPAC_RCCR, 0x07);
}