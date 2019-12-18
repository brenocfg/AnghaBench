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
typedef  int /*<<< orphan*/  u32 ;
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVS_P0_VSR_ADDR ; 
 int /*<<< orphan*/  MVS_P4_VSR_ADDR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mvs_write_port (struct mvs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mvs_write_port_vsr_addr(struct mvs_info *mvi,
						u32 port, u32 addr)
{
	mvs_write_port(mvi, MVS_P0_VSR_ADDR,
			MVS_P4_VSR_ADDR, port, addr);
	mdelay(10);
}