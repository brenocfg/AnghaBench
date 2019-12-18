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
typedef  int u8 ;
struct vc_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u8 mdacon_build_attr(struct vc_data *c, u8 color, u8 intensity, 
			    u8 blink, u8 underline, u8 reverse, u8 italic)
{
	/* The attribute is just a bit vector:
	 *
	 *	Bit 0..1 : intensity (0..2)
	 *	Bit 2    : underline
	 *	Bit 3    : reverse
	 *	Bit 7    : blink
	 */

	return (intensity & 3) |
		((underline & 1) << 2) |
		((reverse   & 1) << 3) |
		(!!italic << 4) |
		((blink     & 1) << 7);
}