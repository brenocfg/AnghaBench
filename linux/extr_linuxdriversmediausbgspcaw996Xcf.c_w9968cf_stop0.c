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
struct sd {int /*<<< orphan*/  jpegqual; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w9968cf_stop0(struct sd *sd)
{
	v4l2_ctrl_grab(sd->jpegqual, false);
	reg_w(sd, 0x39, 0x0000); /* disable JPEG encoder */
	reg_w(sd, 0x16, 0x0000); /* stop video capture */
}