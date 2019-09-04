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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct adv7183 {int /*<<< orphan*/  std; } ;

/* Variables and functions */
 struct adv7183* to_adv7183 (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7183_g_std(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct adv7183 *decoder = to_adv7183(sd);

	*std = decoder->std;
	return 0;
}