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
struct vortex_private {int window; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ SelectWindow ; 
 int /*<<< orphan*/  iowrite16 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void window_set(struct vortex_private *vp, int window)
{
	if (window != vp->window) {
		iowrite16(SelectWindow + window, vp->ioaddr + EL3_CMD);
		vp->window = window;
	}
}