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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_phy_reg (struct fw_ohci*,int) ; 
 int write_phy_reg (struct fw_ohci*,int,int) ; 

__attribute__((used)) static int initiated_reset(struct fw_ohci *ohci)
{
	int reg;
	int ret = 0;

	mutex_lock(&ohci->phy_reg_mutex);
	reg = write_phy_reg(ohci, 7, 0xe0); /* Select page 7 */
	if (reg >= 0) {
		reg = read_phy_reg(ohci, 8);
		reg |= 0x40;
		reg = write_phy_reg(ohci, 8, reg); /* set PMODE bit */
		if (reg >= 0) {
			reg = read_phy_reg(ohci, 12); /* read register 12 */
			if (reg >= 0) {
				if ((reg & 0x08) == 0x08) {
					/* bit 3 indicates "initiated reset" */
					ret = 0x2;
				}
			}
		}
	}
	mutex_unlock(&ohci->phy_reg_mutex);
	return ret;
}