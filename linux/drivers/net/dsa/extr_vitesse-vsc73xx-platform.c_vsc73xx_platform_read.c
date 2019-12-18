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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct vsc73xx_platform {scalar_t__ base_addr; } ;
struct vsc73xx {struct vsc73xx_platform* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  vsc73xx_is_addr_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vsc73xx_make_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc73xx_platform_read(struct vsc73xx *vsc, u8 block, u8 subblock,
				 u8 reg, u32 *val)
{
	struct vsc73xx_platform *vsc_platform = vsc->priv;
	u32 offset;

	if (!vsc73xx_is_addr_valid(block, subblock))
		return -EINVAL;

	offset = vsc73xx_make_addr(block, subblock, reg);
	/* By default vsc73xx running in big-endian mode.
	 * (See "Register Addressing" section 5.5.3 in the VSC7385 manual.)
	 */
	*val = ioread32be(vsc_platform->base_addr + offset);

	return 0;
}