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
struct tegra_fuse {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FUSE_BEGIN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 tegra20_fuse_read_early(struct tegra_fuse *fuse, unsigned int offset)
{
	return readl_relaxed(fuse->base + FUSE_BEGIN + offset);
}