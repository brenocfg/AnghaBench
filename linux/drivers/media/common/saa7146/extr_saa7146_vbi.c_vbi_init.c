#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct saa7146_dev* dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  queue; } ;
struct saa7146_vv {int /*<<< orphan*/  vbi_wq; TYPE_1__ vbi_dmaq; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*,struct saa7146_dev*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_buffer_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vbi_init(struct saa7146_dev *dev, struct saa7146_vv *vv)
{
	DEB_VBI("dev:%p\n", dev);

	INIT_LIST_HEAD(&vv->vbi_dmaq.queue);

	timer_setup(&vv->vbi_dmaq.timeout, saa7146_buffer_timeout, 0);
	vv->vbi_dmaq.dev              = dev;

	init_waitqueue_head(&vv->vbi_wq);
}