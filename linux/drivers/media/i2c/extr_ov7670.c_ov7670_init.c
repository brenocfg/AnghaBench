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
 int /*<<< orphan*/  ov7670_default_regs ; 
 int ov7670_write_array (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7670_init(struct v4l2_subdev *sd, u32 val)
{
	return ov7670_write_array(sd, ov7670_default_regs);
}