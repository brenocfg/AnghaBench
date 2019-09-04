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
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_INTR_MODE_REG ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void netxen_set_interrupt_mode(struct netxen_adapter *adapter,
					     u32 mode)
{
	NXWR32(adapter, NETXEN_INTR_MODE_REG, mode);
}