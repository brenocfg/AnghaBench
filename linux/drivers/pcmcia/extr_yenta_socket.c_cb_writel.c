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
struct yenta_socket {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,struct yenta_socket*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void cb_writel(struct yenta_socket *socket, unsigned reg, u32 val)
{
	debug("%04x %08x\n", socket, reg, val);
	writel(val, socket->base + reg);
	readl(socket->base + reg); /* avoid problems with PCI write posting */
}