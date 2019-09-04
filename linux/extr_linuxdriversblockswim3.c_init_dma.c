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
struct dbdma_cmd {scalar_t__ xfer_status; int /*<<< orphan*/  phy_addr; void* command; void* req_count; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (void*) ; 

__attribute__((used)) static inline void init_dma(struct dbdma_cmd *cp, int cmd,
			    void *buf, int count)
{
	cp->req_count = cpu_to_le16(count);
	cp->command = cpu_to_le16(cmd);
	cp->phy_addr = cpu_to_le32(virt_to_bus(buf));
	cp->xfer_status = 0;
}