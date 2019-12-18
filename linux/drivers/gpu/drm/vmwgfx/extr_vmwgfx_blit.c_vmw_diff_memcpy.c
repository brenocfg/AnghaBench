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
typedef  int /*<<< orphan*/  u8 ;
struct vmw_diff_cpy {size_t cpp; size_t line_offset; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t round_down (size_t,size_t) ; 
 int /*<<< orphan*/  vmw_adjust_rect (struct vmw_diff_cpy*,size_t) ; 
 size_t vmw_find_first_diff (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t) ; 
 size_t vmw_find_last_diff (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t) ; 

void vmw_diff_memcpy(struct vmw_diff_cpy *diff, u8 *dest, const u8 *src,
		     size_t n)
{
	ssize_t csize, byte_len;

	if (WARN_ON_ONCE(round_down(n, diff->cpp) != n))
		return;

	/* TODO: Possibly use a single vmw_find_first_diff per line? */
	csize = vmw_find_first_diff(dest, src, n, diff->cpp);
	if (csize < n) {
		vmw_adjust_rect(diff, csize);
		byte_len = diff->cpp;

		/*
		 * Starting from where first difference was found, find
		 * location of last difference, and then copy.
		 */
		diff->line_offset += csize;
		dest += csize;
		src += csize;
		n -= csize;
		csize = vmw_find_last_diff(dest, src, n, diff->cpp);
		if (csize >= 0) {
			byte_len += csize;
			vmw_adjust_rect(diff, csize);
		}
		memcpy(dest, src, byte_len);
	}
	diff->line_offset += n;
}