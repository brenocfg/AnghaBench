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
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {int* cpp; } ;

/* Variables and functions */
 int cirrus_convert_to (struct drm_framebuffer*) ; 

__attribute__((used)) static int cirrus_cpp(struct drm_framebuffer *fb)
{
	int convert_cpp = cirrus_convert_to(fb);

	if (convert_cpp)
		return convert_cpp;
	return fb->format->cpp[0];
}