#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;
struct saa7146_vv {TYPE_2__ vbi_dmaq; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct saa7146_buf {TYPE_1__ vb; } ;

/* Variables and functions */
 scalar_t__ BUFFER_TIMEOUT ; 
 int /*<<< orphan*/  DEB_VBI (char*,struct saa7146_dev*,struct saa7146_buf*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  VIDEOBUF_ACTIVE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  saa7146_set_vbi_capture (struct saa7146_dev*,struct saa7146_buf*,struct saa7146_buf*) ; 

__attribute__((used)) static int buffer_activate(struct saa7146_dev *dev,
			   struct saa7146_buf *buf,
			   struct saa7146_buf *next)
{
	struct saa7146_vv *vv = dev->vv_data;
	buf->vb.state = VIDEOBUF_ACTIVE;

	DEB_VBI("dev:%p, buf:%p, next:%p\n", dev, buf, next);
	saa7146_set_vbi_capture(dev,buf,next);

	mod_timer(&vv->vbi_dmaq.timeout, jiffies+BUFFER_TIMEOUT);
	return 0;
}