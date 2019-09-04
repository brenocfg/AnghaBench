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
typedef  int u8 ;
struct ks8851_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MK_OP (int,unsigned int) ; 
 int /*<<< orphan*/  ks8851_rdreg (struct ks8851_net*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static unsigned ks8851_rdreg8(struct ks8851_net *ks, unsigned reg)
{
	u8 rxb[1];

	ks8851_rdreg(ks, MK_OP(1 << (reg & 3), reg), rxb, 1);
	return rxb[0];
}