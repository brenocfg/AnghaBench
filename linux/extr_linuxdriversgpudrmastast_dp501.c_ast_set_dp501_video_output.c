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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_write_cmd (struct drm_device*,int) ; 
 int /*<<< orphan*/  ast_write_data (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

void ast_set_dp501_video_output(struct drm_device *dev, u8 mode)
{
	ast_write_cmd(dev, 0x40);
	ast_write_data(dev, mode);

	msleep(10);
}