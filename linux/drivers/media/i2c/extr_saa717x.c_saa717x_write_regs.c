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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa717x_write (struct v4l2_subdev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void saa717x_write_regs(struct v4l2_subdev *sd, u32 *data)
{
	while (data[0] || data[1]) {
		saa717x_write(sd, data[0], data[1]);
		data += 2;
	}
}