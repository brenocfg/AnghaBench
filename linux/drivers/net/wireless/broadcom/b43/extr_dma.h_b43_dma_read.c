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
typedef  scalar_t__ u16 ;
struct b43_dmaring {scalar_t__ mmio_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_read32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 b43_dma_read(struct b43_dmaring *ring, u16 offset)
{
	return b43_read32(ring->dev, ring->mmio_base + offset);
}