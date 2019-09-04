#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* curr; } ;
struct saa7146_vv {int vbi_fieldcount; TYPE_3__ vbi_dmaq; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; struct saa7146_vv* vv_data; } ;
struct TYPE_5__ {int field_count; } ;
struct TYPE_6__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*,struct saa7146_dev*,...) ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  saa7146_buffer_finish (struct saa7146_dev*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_buffer_next (struct saa7146_dev*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vbi_irq_done(struct saa7146_dev *dev, unsigned long status)
{
	struct saa7146_vv *vv = dev->vv_data;
	spin_lock(&dev->slock);

	if (vv->vbi_dmaq.curr) {
		DEB_VBI("dev:%p, curr:%p\n", dev, vv->vbi_dmaq.curr);
		/* this must be += 2, one count for each field */
		vv->vbi_fieldcount+=2;
		vv->vbi_dmaq.curr->vb.field_count = vv->vbi_fieldcount;
		saa7146_buffer_finish(dev, &vv->vbi_dmaq, VIDEOBUF_DONE);
	} else {
		DEB_VBI("dev:%p\n", dev);
	}
	saa7146_buffer_next(dev, &vv->vbi_dmaq, 1);

	spin_unlock(&dev->slock);
}