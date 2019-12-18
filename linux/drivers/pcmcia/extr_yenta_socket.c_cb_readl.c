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

__attribute__((used)) static inline u32 cb_readl(struct yenta_socket *socket, unsigned reg)
{
	u32 val = readl(socket->base + reg);
	debug("%04x %08x\n", socket, reg, val);
	return val;
}