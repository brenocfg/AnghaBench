#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct bgmac {TYPE_1__ plat; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 platform_bgmac_read(struct bgmac *bgmac, u16 offset)
{
	return readl(bgmac->plat.base + offset);
}