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
struct bm_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ BMAN_REV20 ; 
 scalar_t__ BMAN_REV21 ; 
 int BMAN_TOKEN_MASK ; 
 int bm_buffer_get64 (struct bm_buffer const*) ; 
 scalar_t__ bman_ip_rev ; 

__attribute__((used)) static inline int bufs_cmp(const struct bm_buffer *a, const struct bm_buffer *b)
{
	if (bman_ip_rev == BMAN_REV20 || bman_ip_rev == BMAN_REV21) {

		/*
		 * On SoCs with BMan revison 2.0, BMan only respects the 40
		 * LS-bits of buffer addresses, masking off the upper 8-bits on
		 * release commands. The API provides for 48-bit addresses
		 * because some SoCs support all 48-bits. When generating
		 * garbage addresses for testing, we either need to zero the
		 * upper 8-bits when releasing to BMan (otherwise we'll be
		 * disappointed when the buffers we acquire back from BMan
		 * don't match), or we need to mask the upper 8-bits off when
		 * comparing. We do the latter.
		 */
		if ((bm_buffer_get64(a) & BMAN_TOKEN_MASK) <
		    (bm_buffer_get64(b) & BMAN_TOKEN_MASK))
			return -1;
		if ((bm_buffer_get64(a) & BMAN_TOKEN_MASK) >
		    (bm_buffer_get64(b) & BMAN_TOKEN_MASK))
			return 1;
	} else {
		if (bm_buffer_get64(a) < bm_buffer_get64(b))
			return -1;
		if (bm_buffer_get64(a) > bm_buffer_get64(b))
			return 1;
	}

	return 0;
}