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
struct rot_context {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int /*<<< orphan*/  ROT_CONTROL ; 
 int /*<<< orphan*/  ROT_CONTROL_FLIP_HORIZONTAL ; 
 int /*<<< orphan*/  ROT_CONTROL_FLIP_MASK ; 
 int /*<<< orphan*/  ROT_CONTROL_FLIP_VERTICAL ; 
 int /*<<< orphan*/  ROT_CONTROL_ROT_180 ; 
 int /*<<< orphan*/  ROT_CONTROL_ROT_270 ; 
 int /*<<< orphan*/  ROT_CONTROL_ROT_90 ; 
 int /*<<< orphan*/  ROT_CONTROL_ROT_MASK ; 
 int /*<<< orphan*/  rot_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rot_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rotator_dst_set_transf(struct rot_context *rot,
				   unsigned int rotation)
{
	u32 val;

	/* Set transform configuration */
	val = rot_read(ROT_CONTROL);
	val &= ~ROT_CONTROL_FLIP_MASK;

	if (rotation & DRM_MODE_REFLECT_X)
		val |= ROT_CONTROL_FLIP_VERTICAL;
	if (rotation & DRM_MODE_REFLECT_Y)
		val |= ROT_CONTROL_FLIP_HORIZONTAL;

	val &= ~ROT_CONTROL_ROT_MASK;

	if (rotation & DRM_MODE_ROTATE_90)
		val |= ROT_CONTROL_ROT_90;
	else if (rotation & DRM_MODE_ROTATE_180)
		val |= ROT_CONTROL_ROT_180;
	else if (rotation & DRM_MODE_ROTATE_270)
		val |= ROT_CONTROL_ROT_270;

	rot_write(val, ROT_CONTROL);
}