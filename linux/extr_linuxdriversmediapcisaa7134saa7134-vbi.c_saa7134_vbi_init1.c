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
struct TYPE_2__ {struct saa7134_dev* dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  queue; } ;
struct saa7134_dev {TYPE_1__ vbi_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  saa7134_buffer_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vbibufs ; 

int saa7134_vbi_init1(struct saa7134_dev *dev)
{
	INIT_LIST_HEAD(&dev->vbi_q.queue);
	timer_setup(&dev->vbi_q.timeout, saa7134_buffer_timeout, 0);
	dev->vbi_q.dev              = dev;

	if (vbibufs < 2)
		vbibufs = 2;
	if (vbibufs > VIDEO_MAX_FRAME)
		vbibufs = VIDEO_MAX_FRAME;
	return 0;
}