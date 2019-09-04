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
struct nvkm_fb {int page; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
gv100_fb_init_page(struct nvkm_fb *fb)
{
	return (fb->page == 16) ? 0 : -EINVAL;
}