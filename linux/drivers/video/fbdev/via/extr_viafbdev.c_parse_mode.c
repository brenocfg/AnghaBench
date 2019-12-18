#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fb_videomode {scalar_t__ xres; scalar_t__ yres; } ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_31; int /*<<< orphan*/  i2c_26; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VIA_CRT ; 
 scalar_t__ VIA_DVP1 ; 
 scalar_t__ machine_is_olpc () ; 
 scalar_t__ simple_strtoul (char const*,char**,int) ; 
 struct fb_videomode* via_aux_get_preferred_mode (int /*<<< orphan*/ ) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static int parse_mode(const char *str, u32 devices, u32 *xres, u32 *yres)
{
	const struct fb_videomode *mode = NULL;
	char *ptr;

	if (!str) {
		if (devices == VIA_CRT)
			mode = via_aux_get_preferred_mode(
				viaparinfo->shared->i2c_26);
		else if (devices == VIA_DVP1)
			mode = via_aux_get_preferred_mode(
				viaparinfo->shared->i2c_31);

		if (mode) {
			*xres = mode->xres;
			*yres = mode->yres;
		} else if (machine_is_olpc()) {
			*xres = 1200;
			*yres = 900;
		} else {
			*xres = 640;
			*yres = 480;
		}
		return 0;
	}

	*xres = simple_strtoul(str, &ptr, 10);
	if (ptr[0] != 'x')
		return -EINVAL;

	*yres = simple_strtoul(&ptr[1], &ptr, 10);
	if (ptr[0])
		return -EINVAL;

	return 0;
}