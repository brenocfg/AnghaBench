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

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,char const*,unsigned int,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 unsigned int R128_REQUIRE_QUIESCENCE ; 
 unsigned int R128_UPLOAD_CLIPRECTS ; 
 unsigned int R128_UPLOAD_CONTEXT ; 
 unsigned int R128_UPLOAD_CORE ; 
 unsigned int R128_UPLOAD_MASKS ; 
 unsigned int R128_UPLOAD_SETUP ; 
 unsigned int R128_UPLOAD_TEX0 ; 
 unsigned int R128_UPLOAD_TEX1 ; 
 unsigned int R128_UPLOAD_WINDOW ; 

__attribute__((used)) static void r128_print_dirty(const char *msg, unsigned int flags)
{
	DRM_INFO("%s: (0x%x) %s%s%s%s%s%s%s%s%s\n",
		 msg,
		 flags,
		 (flags & R128_UPLOAD_CORE) ? "core, " : "",
		 (flags & R128_UPLOAD_CONTEXT) ? "context, " : "",
		 (flags & R128_UPLOAD_SETUP) ? "setup, " : "",
		 (flags & R128_UPLOAD_TEX0) ? "tex0, " : "",
		 (flags & R128_UPLOAD_TEX1) ? "tex1, " : "",
		 (flags & R128_UPLOAD_MASKS) ? "masks, " : "",
		 (flags & R128_UPLOAD_WINDOW) ? "window, " : "",
		 (flags & R128_UPLOAD_CLIPRECTS) ? "cliprects, " : "",
		 (flags & R128_REQUIRE_QUIESCENCE) ? "quiescence, " : "");
}