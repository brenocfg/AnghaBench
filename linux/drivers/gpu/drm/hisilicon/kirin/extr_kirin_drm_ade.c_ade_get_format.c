#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ pixel_format; scalar_t__ hw_format; } ;

/* Variables and functions */
 scalar_t__ ADE_FORMAT_UNSUPPORT ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 TYPE_1__* ade_formats ; 

__attribute__((used)) static u32 ade_get_format(u32 pixel_format)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ade_formats); i++)
		if (ade_formats[i].pixel_format == pixel_format)
			return ade_formats[i].hw_format;

	/* not found */
	DRM_ERROR("Not found pixel format!!fourcc_format= %d\n",
		  pixel_format);
	return ADE_FORMAT_UNSUPPORT;
}