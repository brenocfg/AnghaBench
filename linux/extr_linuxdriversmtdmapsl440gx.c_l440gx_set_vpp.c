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
struct map_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPP_PORT ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l440gx_vpp_lock ; 
 int l440gx_vpp_refcnt ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void l440gx_set_vpp(struct map_info *map, int vpp)
{
	unsigned long flags;

	spin_lock_irqsave(&l440gx_vpp_lock, flags);
	if (vpp) {
		if (++l440gx_vpp_refcnt == 1)   /* first nested 'on' */
			outl(inl(VPP_PORT) | 1, VPP_PORT);
	} else {
		if (--l440gx_vpp_refcnt == 0)   /* last nested 'off' */
			outl(inl(VPP_PORT) & ~1, VPP_PORT);
	}
	spin_unlock_irqrestore(&l440gx_vpp_lock, flags);
}