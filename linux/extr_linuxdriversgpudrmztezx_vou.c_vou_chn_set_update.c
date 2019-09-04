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
struct zx_crtc {scalar_t__ chnreg; } ;

/* Variables and functions */
 scalar_t__ CHN_UPDATE ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int) ; 

__attribute__((used)) static inline void vou_chn_set_update(struct zx_crtc *zcrtc)
{
	zx_writel(zcrtc->chnreg + CHN_UPDATE, 1);
}