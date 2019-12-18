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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct tegra_fuse {unsigned int (* read ) (struct tegra_fuse*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  round_down (unsigned int,int) ; 
 unsigned int stub1 (struct tegra_fuse*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 fuse_readb(struct tegra_fuse *fuse, unsigned int offset)
{
	u32 val;

	val = fuse->read(fuse, round_down(offset, 4));
	val >>= (offset % 4) * 8;
	val &= 0xff;

	return val;
}