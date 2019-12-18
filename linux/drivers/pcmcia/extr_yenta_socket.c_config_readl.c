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
struct yenta_socket {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,struct yenta_socket*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 config_readl(struct yenta_socket *socket, unsigned offset)
{
	u32 val;
	pci_read_config_dword(socket->dev, offset, &val);
	debug("%04x %08x\n", socket, offset, val);
	return val;
}