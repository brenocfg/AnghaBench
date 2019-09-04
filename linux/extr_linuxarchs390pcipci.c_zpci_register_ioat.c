#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct zpci_fib {int pba; int pal; int iota; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ZPCI_IOTA_RTTO_FLAG ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_REG_IOAT ; 
 scalar_t__ zpci_mod_fc (int,struct zpci_fib*,int /*<<< orphan*/ *) ; 

int zpci_register_ioat(struct zpci_dev *zdev, u8 dmaas,
		       u64 base, u64 limit, u64 iota)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, dmaas, ZPCI_MOD_FC_REG_IOAT);
	struct zpci_fib fib = {0};
	u8 status;

	WARN_ON_ONCE(iota & 0x3fff);
	fib.pba = base;
	fib.pal = limit;
	fib.iota = iota | ZPCI_IOTA_RTTO_FLAG;
	return zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
}