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
struct ks8851_net {int dummy; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  MK_OP (int,unsigned int) ; 
 int /*<<< orphan*/  ks8851_rdreg (struct ks8851_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static unsigned ks8851_rdreg16(struct ks8851_net *ks, unsigned reg)
{
	__le16 rx = 0;

	ks8851_rdreg(ks, MK_OP(reg & 2 ? 0xC : 0x3, reg), (u8 *)&rx, 2);
	return le16_to_cpu(rx);
}