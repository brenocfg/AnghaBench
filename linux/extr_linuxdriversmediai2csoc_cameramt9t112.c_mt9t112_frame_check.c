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

/* Variables and functions */
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  soc_camera_limit_side (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt9t112_frame_check(u32 *width, u32 *height, u32 *left, u32 *top)
{
	soc_camera_limit_side(left, width, 0, 0, MAX_WIDTH);
	soc_camera_limit_side(top, height, 0, 0, MAX_HEIGHT);
}