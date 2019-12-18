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
struct mcam_camera {int next_buf; int nbufs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CF_FRAME_SOF0 ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcam_reset_buffers(struct mcam_camera *cam)
{
	int i;

	cam->next_buf = -1;
	for (i = 0; i < cam->nbufs; i++) {
		clear_bit(i, &cam->flags);
		clear_bit(CF_FRAME_SOF0 + i, &cam->flags);
	}
}