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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_clip_det_nphy(struct brcms_phy *pi, u8 write, u16 *vals)
{

	if (write == 0) {
		vals[0] = read_phy_reg(pi, 0x2c);
		vals[1] = read_phy_reg(pi, 0x42);
	} else {
		write_phy_reg(pi, 0x2c, vals[0]);
		write_phy_reg(pi, 0x42, vals[1]);
	}
}