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
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  MK_OP (int,unsigned int) ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  ks8851_rdreg (struct ks8851_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static unsigned ks8851_rdreg32(struct ks8851_net *ks, unsigned reg)
{
	__le32 rx = 0;

	WARN_ON(reg & 3);

	ks8851_rdreg(ks, MK_OP(0xf, reg), (u8 *)&rx, 4);
	return le32_to_cpu(rx);
}