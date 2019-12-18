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
typedef  int u64 ;
struct wil_ring_dma_addr {int /*<<< orphan*/  addr_high; int /*<<< orphan*/  addr_low; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t wil_desc_addr(struct wil_ring_dma_addr *addr)
{
	return le32_to_cpu(addr->addr_low) |
			   ((u64)le16_to_cpu(addr->addr_high) << 32);
}