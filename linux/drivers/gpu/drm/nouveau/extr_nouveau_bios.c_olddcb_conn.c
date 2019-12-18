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
typedef  int u8 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int* olddcb_conntab (struct drm_device*) ; 

u8 *
olddcb_conn(struct drm_device *dev, u8 idx)
{
	u8 *conntab = olddcb_conntab(dev);
	if (conntab && idx < conntab[2])
		return conntab + conntab[1] + (idx * conntab[3]);
	return NULL;
}