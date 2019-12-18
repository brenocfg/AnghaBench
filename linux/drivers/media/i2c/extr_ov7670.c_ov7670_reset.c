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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM7_RESET ; 
 int /*<<< orphan*/  REG_COM7 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7670_reset(struct v4l2_subdev *sd, u32 val)
{
	ov7670_write(sd, REG_COM7, COM7_RESET);
	msleep(1);
	return 0;
}