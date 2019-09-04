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
typedef  int /*<<< orphan*/  u64 ;
struct zpci_fib {int sum; unsigned long aibv; unsigned long aisb; int aisbo; scalar_t__ aibvo; int /*<<< orphan*/  noi; int /*<<< orphan*/  isc; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int aisb; TYPE_2__* aibv; int /*<<< orphan*/  fh; } ;
struct TYPE_4__ {scalar_t__ vector; } ;
struct TYPE_3__ {scalar_t__ vector; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_ISC ; 
 int /*<<< orphan*/  ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_REG_INT ; 
 int /*<<< orphan*/  airq_iv_end (TYPE_2__*) ; 
 TYPE_1__* zpci_aisb_iv ; 
 scalar_t__ zpci_mod_fc (int /*<<< orphan*/ ,struct zpci_fib*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zpci_set_airq(struct zpci_dev *zdev)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_REG_INT);
	struct zpci_fib fib = {0};
	u8 status;

	fib.isc = PCI_ISC;
	fib.sum = 1;		/* enable summary notifications */
	fib.noi = airq_iv_end(zdev->aibv);
	fib.aibv = (unsigned long) zdev->aibv->vector;
	fib.aibvo = 0;		/* each zdev has its own interrupt vector */
	fib.aisb = (unsigned long) zpci_aisb_iv->vector + (zdev->aisb/64)*8;
	fib.aisbo = zdev->aisb & 63;

	return zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
}