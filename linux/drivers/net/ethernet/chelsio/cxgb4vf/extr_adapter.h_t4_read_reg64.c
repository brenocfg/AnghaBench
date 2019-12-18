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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct adapter {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static inline u64 t4_read_reg64(struct adapter *adapter, u32 reg_addr)
{
	return readq(adapter->regs + reg_addr);
}