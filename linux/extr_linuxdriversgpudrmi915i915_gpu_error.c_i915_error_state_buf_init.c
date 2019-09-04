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
struct drm_i915_private {int dummy; } ;
struct drm_i915_error_state_buf {size_t size; int /*<<< orphan*/  start; int /*<<< orphan*/ * buf; struct drm_i915_private* i915; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 void* kmalloc (size_t,int) ; 
 int /*<<< orphan*/  memset (struct drm_i915_error_state_buf*,int /*<<< orphan*/ ,int) ; 

int i915_error_state_buf_init(struct drm_i915_error_state_buf *ebuf,
			      struct drm_i915_private *i915,
			      size_t count, loff_t pos)
{
	memset(ebuf, 0, sizeof(*ebuf));
	ebuf->i915 = i915;

	/* We need to have enough room to store any i915_error_state printf
	 * so that we can move it to start position.
	 */
	ebuf->size = count + 1 > PAGE_SIZE ? count + 1 : PAGE_SIZE;
	ebuf->buf = kmalloc(ebuf->size,
				GFP_KERNEL | __GFP_NORETRY | __GFP_NOWARN);

	if (ebuf->buf == NULL) {
		ebuf->size = PAGE_SIZE;
		ebuf->buf = kmalloc(ebuf->size, GFP_KERNEL);
	}

	if (ebuf->buf == NULL) {
		ebuf->size = 128;
		ebuf->buf = kmalloc(ebuf->size, GFP_KERNEL);
	}

	if (ebuf->buf == NULL)
		return -ENOMEM;

	ebuf->start = pos;

	return 0;
}