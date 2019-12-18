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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int read_radio_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

void xor_radio_reg(struct brcms_phy *pi, u16 addr, u16 mask)
{
	u16 rval;

	rval = read_radio_reg(pi, addr);
	write_radio_reg(pi, addr, (rval ^ mask));
}