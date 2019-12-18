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
struct fdp1_field_buffer {int /*<<< orphan*/  vb; scalar_t__ last_field; } ;
struct fdp1_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_field_complete(struct fdp1_ctx *ctx,
				struct fdp1_field_buffer *fbuf)
{
	/* job->previous may be on the first field */
	if (!fbuf)
		return;

	if (fbuf->last_field)
		v4l2_m2m_buf_done(fbuf->vb, VB2_BUF_STATE_DONE);
}