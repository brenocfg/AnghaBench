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
typedef  int /*<<< orphan*/  verifier_state_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  drm_via_private_t ;

/* Variables and functions */
 int HALCYON_HEADER1 ; 
 int HALCYON_HEADER1MASK ; 
 int /*<<< orphan*/  VIA_WRITE (int,int const) ; 
 int /*<<< orphan*/  state_command ; 

__attribute__((used)) static __inline__ verifier_state_t
via_parse_header1(drm_via_private_t *dev_priv, uint32_t const **buffer,
		  const uint32_t *buf_end)
{
	register uint32_t cmd;
	const uint32_t *buf = *buffer;

	while (buf < buf_end) {
		cmd = *buf;
		if ((cmd & HALCYON_HEADER1MASK) != HALCYON_HEADER1)
			break;
		VIA_WRITE((cmd & ~HALCYON_HEADER1MASK) << 2, *++buf);
		buf++;
	}
	*buffer = buf;
	return state_command;
}