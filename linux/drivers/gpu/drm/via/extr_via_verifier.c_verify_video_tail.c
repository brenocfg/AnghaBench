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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

__attribute__((used)) static __inline__ int
verify_video_tail(uint32_t const **buffer, const uint32_t * buf_end,
		  uint32_t dwords)
{
	const uint32_t *buf = *buffer;

	if (buf_end - buf < dwords) {
		DRM_ERROR("Illegal termination of video command.\n");
		return 1;
	}
	while (dwords--) {
		if (*buf++) {
			DRM_ERROR("Illegal video command tail.\n");
			return 1;
		}
	}
	*buffer = buf;
	return 0;
}