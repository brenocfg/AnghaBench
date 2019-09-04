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
struct fw_ohci {int /*<<< orphan*/  phy_reg_mutex; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_phy_reg (struct fw_ohci*,int) ; 

__attribute__((used)) static int ohci_read_phy_reg(struct fw_card *card, int addr)
{
	struct fw_ohci *ohci = fw_ohci(card);
	int ret;

	mutex_lock(&ohci->phy_reg_mutex);
	ret = read_phy_reg(ohci, addr);
	mutex_unlock(&ohci->phy_reg_mutex);

	return ret;
}