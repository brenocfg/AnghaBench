#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CARDBUS_SOCKET_REGS_BASE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cardbus_socket_writel(vrc4173_socket_t *socket, u16 offset, uint32_t val)
{
	writel(val, socket->base + CARDBUS_SOCKET_REGS_BASE + offset);
}