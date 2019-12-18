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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtw_pci {scalar_t__ mmap; } ;
struct rtw_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtw_pci_write16(struct rtw_dev *rtwdev, u32 addr, u16 val)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;

	writew(val, rtwpci->mmap + addr);
}