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
struct rockchip_rga {int dummy; } ;

/* Variables and functions */
 int rga_read (struct rockchip_rga*,int) ; 
 int /*<<< orphan*/  rga_write (struct rockchip_rga*,int,int) ; 

__attribute__((used)) static inline void rga_mod(struct rockchip_rga *rga, u32 reg, u32 val, u32 mask)
{
	u32 temp = rga_read(rga, reg) & ~(mask);

	temp |= val & mask;
	rga_write(rga, reg, temp);
}