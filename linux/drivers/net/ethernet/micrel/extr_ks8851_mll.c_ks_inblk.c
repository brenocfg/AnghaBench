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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ks_net {int /*<<< orphan*/  hw_addr; } ;

/* Variables and functions */
 scalar_t__ ioread16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ks_inblk(struct ks_net *ks, u16 *wptr, u32 len)
{
	len >>= 1;
	while (len--)
		*wptr++ = (u16)ioread16(ks->hw_addr);
}