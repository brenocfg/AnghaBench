#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  field; } ;
struct unicam_device {TYPE_2__* next_frm; TYPE_2__* cur_frm; int /*<<< orphan*/  sequence; TYPE_1__ m_fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  vb2_buf; scalar_t__ sequence; int /*<<< orphan*/  field; } ;
struct TYPE_5__ {TYPE_3__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void unicam_process_buffer_complete(struct unicam_device *dev)
{
	dev->cur_frm->vb.field = dev->m_fmt.field;
	dev->cur_frm->vb.sequence = dev->sequence++;

	vb2_buffer_done(&dev->cur_frm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	dev->cur_frm = dev->next_frm;
}