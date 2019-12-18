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
struct v4l2_tuner {int /*<<< orphan*/  audmode; } ;
struct mxb {int /*<<< orphan*/  cur_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tda9840_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static void mxb_update_audmode(struct mxb *mxb)
{
	struct v4l2_tuner t = {
		.audmode = mxb->cur_mode,
	};

	tda9840_call(mxb, tuner, s_tuner, &t);
}