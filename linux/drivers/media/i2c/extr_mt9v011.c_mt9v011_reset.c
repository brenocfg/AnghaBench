#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* mt9v011_init_default ; 
 int /*<<< orphan*/  mt9v011_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_balance (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  set_read_mode (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  set_res (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v011_reset(struct v4l2_subdev *sd, u32 val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mt9v011_init_default); i++)
		mt9v011_write(sd, mt9v011_init_default[i].reg,
			       mt9v011_init_default[i].value);

	set_balance(sd);
	set_res(sd);
	set_read_mode(sd);

	return 0;
}