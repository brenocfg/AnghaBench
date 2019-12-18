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
struct saa6752hs_state {int /*<<< orphan*/  standard; } ;

/* Variables and functions */
 struct saa6752hs_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa6752hs_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa6752hs_state *h = to_state(sd);

	h->standard = std;
	return 0;
}