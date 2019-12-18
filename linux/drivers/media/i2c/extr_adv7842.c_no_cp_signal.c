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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int cp_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static inline bool no_cp_signal(struct v4l2_subdev *sd)
{
	return ((cp_read(sd, 0xb5) & 0xd0) != 0xd0) || !(cp_read(sd, 0xb1) & 0x80);
}