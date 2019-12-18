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
struct intel_engine_cs {char* name; } ;
struct drm_i915_error_state_buf {int dummy; } ;
struct drm_i915_error_object {int page_count; int /*<<< orphan*/ ** pages; scalar_t__ unused; int /*<<< orphan*/  gtt_offset; } ;

/* Variables and functions */
 int ASCII85_BUFSZ ; 
 int PAGE_SIZE ; 
 char* ascii85_encode (int /*<<< orphan*/ ,char*) ; 
 int ascii85_encode_len (int) ; 
 int /*<<< orphan*/  err_compression_marker (struct drm_i915_error_state_buf*) ; 
 int /*<<< orphan*/  err_printf (struct drm_i915_error_state_buf*,char*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_puts (struct drm_i915_error_state_buf*,char*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_error_obj(struct drm_i915_error_state_buf *m,
			    const struct intel_engine_cs *engine,
			    const char *name,
			    const struct drm_i915_error_object *obj)
{
	char out[ASCII85_BUFSZ];
	int page;

	if (!obj)
		return;

	if (name) {
		err_printf(m, "%s --- %s = 0x%08x %08x\n",
			   engine ? engine->name : "global", name,
			   upper_32_bits(obj->gtt_offset),
			   lower_32_bits(obj->gtt_offset));
	}

	err_compression_marker(m);
	for (page = 0; page < obj->page_count; page++) {
		int i, len;

		len = PAGE_SIZE;
		if (page == obj->page_count - 1)
			len -= obj->unused;
		len = ascii85_encode_len(len);

		for (i = 0; i < len; i++)
			err_puts(m, ascii85_encode(obj->pages[page][i], out));
	}
	err_puts(m, "\n");
}