#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct TYPE_8__ {TYPE_3__ fmt; } ;
struct vpfe_device {TYPE_1__* next_frm; TYPE_1__* cur_frm; TYPE_4__ fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  done; int /*<<< orphan*/  size; int /*<<< orphan*/  state; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vpfe_process_buffer_complete(struct vpfe_device *vpfe_dev)
{
	vpfe_dev->cur_frm->ts = ktime_get_ns();
	vpfe_dev->cur_frm->state = VIDEOBUF_DONE;
	vpfe_dev->cur_frm->size = vpfe_dev->fmt.fmt.pix.sizeimage;
	wake_up_interruptible(&vpfe_dev->cur_frm->done);
	vpfe_dev->cur_frm = vpfe_dev->next_frm;
}