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
typedef  int /*<<< orphan*/  u32 ;
struct drm_printer {int dummy; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,...) ; 
 int hex_dump_to_buffer (void const*,size_t,size_t const,int,char*,int,int) ; 
 int /*<<< orphan*/  memcmp (void const*,void const*,size_t const) ; 

__attribute__((used)) static void hexdump(struct drm_printer *m, const void *buf, size_t len)
{
	const size_t rowsize = 8 * sizeof(u32);
	const void *prev = NULL;
	bool skip = false;
	size_t pos;

	for (pos = 0; pos < len; pos += rowsize) {
		char line[128];

		if (prev && !memcmp(prev, buf + pos, rowsize)) {
			if (!skip) {
				drm_printf(m, "*\n");
				skip = true;
			}
			continue;
		}

		WARN_ON_ONCE(hex_dump_to_buffer(buf + pos, len - pos,
						rowsize, sizeof(u32),
						line, sizeof(line),
						false) >= sizeof(line));
		drm_printf(m, "[%04zx] %s\n", pos, line);

		prev = buf + pos;
		skip = false;
	}
}