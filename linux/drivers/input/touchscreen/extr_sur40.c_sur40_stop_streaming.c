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
struct vb2_queue {int dummy; } ;
struct sur40_state {int sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  return_all_buffers (struct sur40_state*,int /*<<< orphan*/ ) ; 
 struct sur40_state* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_wait_for_all_buffers (struct vb2_queue*) ; 

__attribute__((used)) static void sur40_stop_streaming(struct vb2_queue *vq)
{
	struct sur40_state *sur40 = vb2_get_drv_priv(vq);
	vb2_wait_for_all_buffers(vq);
	sur40->sequence = -1;

	/* Release all active buffers */
	return_all_buffers(sur40, VB2_BUF_STATE_ERROR);
}