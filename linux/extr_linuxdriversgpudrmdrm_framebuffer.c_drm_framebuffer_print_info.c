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
struct drm_printer {int dummy; } ;
struct drm_framebuffer {unsigned int width; char* height; char** pitches; char** offsets; scalar_t__* obj; TYPE_1__* format; int /*<<< orphan*/  modifier; int /*<<< orphan*/  comm; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_2__ {unsigned int num_planes; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_plane_height (char*,struct drm_framebuffer const*,unsigned int) ; 
 int /*<<< orphan*/  drm_framebuffer_plane_width (unsigned int,struct drm_framebuffer const*,unsigned int) ; 
 int /*<<< orphan*/  drm_framebuffer_read_refcount (struct drm_framebuffer const*) ; 
 int /*<<< orphan*/  drm_gem_print_info (struct drm_printer*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  drm_printf_indent (struct drm_printer*,unsigned int,char*,...) ; 

void drm_framebuffer_print_info(struct drm_printer *p, unsigned int indent,
				const struct drm_framebuffer *fb)
{
	struct drm_format_name_buf format_name;
	unsigned int i;

	drm_printf_indent(p, indent, "allocated by = %s\n", fb->comm);
	drm_printf_indent(p, indent, "refcount=%u\n",
			  drm_framebuffer_read_refcount(fb));
	drm_printf_indent(p, indent, "format=%s\n",
			  drm_get_format_name(fb->format->format, &format_name));
	drm_printf_indent(p, indent, "modifier=0x%llx\n", fb->modifier);
	drm_printf_indent(p, indent, "size=%ux%u\n", fb->width, fb->height);
	drm_printf_indent(p, indent, "layers:\n");

	for (i = 0; i < fb->format->num_planes; i++) {
		drm_printf_indent(p, indent + 1, "size[%u]=%dx%d\n", i,
				  drm_framebuffer_plane_width(fb->width, fb, i),
				  drm_framebuffer_plane_height(fb->height, fb, i));
		drm_printf_indent(p, indent + 1, "pitch[%u]=%u\n", i, fb->pitches[i]);
		drm_printf_indent(p, indent + 1, "offset[%u]=%u\n", i, fb->offsets[i]);
		drm_printf_indent(p, indent + 1, "obj[%u]:%s\n", i,
				  fb->obj[i] ? "" : "(null)");
		if (fb->obj[i])
			drm_gem_print_info(p, indent + 2, fb->obj[i]);
	}
}