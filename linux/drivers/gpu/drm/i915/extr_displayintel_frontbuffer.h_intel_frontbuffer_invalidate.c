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
struct intel_frontbuffer {int /*<<< orphan*/  bits; } ;
typedef  enum fb_op_origin { ____Placeholder_fb_op_origin } fb_op_origin ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_fb_invalidate (struct intel_frontbuffer*,int,unsigned int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool intel_frontbuffer_invalidate(struct intel_frontbuffer *front,
						enum fb_op_origin origin)
{
	unsigned int frontbuffer_bits;

	if (!front)
		return false;

	frontbuffer_bits = atomic_read(&front->bits);
	if (!frontbuffer_bits)
		return false;

	__intel_fb_invalidate(front, origin, frontbuffer_bits);
	return true;
}