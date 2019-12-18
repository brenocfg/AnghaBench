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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int extif_read32 (struct ssb_extif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extif_write32 (struct ssb_extif*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 extif_write32_masked(struct ssb_extif *extif, u16 offset,
				       u32 mask, u32 value)
{
	value &= mask;
	value |= extif_read32(extif, offset) & ~mask;
	extif_write32(extif, offset, value);

	return value;
}