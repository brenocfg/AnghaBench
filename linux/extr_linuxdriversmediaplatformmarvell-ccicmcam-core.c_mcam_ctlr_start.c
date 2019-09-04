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
struct mcam_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C0_ENABLE ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  mcam_reg_set_bit (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcam_ctlr_start(struct mcam_camera *cam)
{
	/* set_bit performs a read, so no other barrier should be
	   needed here */
	mcam_reg_set_bit(cam, REG_CTRL0, C0_ENABLE);
}