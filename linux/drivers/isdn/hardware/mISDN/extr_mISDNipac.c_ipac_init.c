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
typedef  int /*<<< orphan*/  u8 ;
struct ipac_hw {int type; int /*<<< orphan*/  isac; int /*<<< orphan*/  name; TYPE_2__* hscx; int /*<<< orphan*/  conf; } ;
struct TYPE_3__ {int debug; } ;
struct TYPE_4__ {TYPE_1__ bch; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int /*<<< orphan*/  IPAC_CONF ; 
 int /*<<< orphan*/  IPAC_ID ; 
 int /*<<< orphan*/  IPAC_MASK ; 
 int IPAC_TYPE_HSCX ; 
 int IPAC_TYPE_IPAC ; 
 int /*<<< orphan*/  IPAC__ON ; 
 int /*<<< orphan*/  ReadIPAC (struct ipac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteIPAC (struct ipac_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hscx_init (TYPE_2__*) ; 
 int isac_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipac_init(struct ipac_hw *ipac)
{
	u8 val;

	if (ipac->type & IPAC_TYPE_HSCX) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		val = ReadIPAC(ipac, IPAC_ID);
	} else if (ipac->type & IPAC_TYPE_IPAC) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		WriteIPAC(ipac, IPAC_MASK, IPAC__ON);
		val = ReadIPAC(ipac, IPAC_CONF);
		/* conf is default 0, but can be overwritten by card setup */
		pr_debug("%s: IPAC CONF %02x/%02x\n", ipac->name,
			 val, ipac->conf);
		WriteIPAC(ipac, IPAC_CONF, ipac->conf);
		val = ReadIPAC(ipac, IPAC_ID);
		if (ipac->hscx[0].bch.debug & DEBUG_HW)
			pr_notice("%s: IPAC Design ID %02x\n", ipac->name, val);
	}
	/* nothing special for IPACX to do here */
	return isac_init(&ipac->isac);
}