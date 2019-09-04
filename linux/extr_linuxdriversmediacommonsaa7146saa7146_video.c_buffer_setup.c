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
struct videobuf_queue {struct file* priv_data; } ;
struct TYPE_3__ {unsigned int sizeimage; } ;
struct saa7146_vv {TYPE_1__ video_fmt; } ;
struct saa7146_fh {TYPE_2__* dev; } ;
struct file {struct saa7146_fh* private_data; } ;
struct TYPE_4__ {struct saa7146_vv* vv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_CAP (char*,unsigned int,unsigned int) ; 
 unsigned int MAX_SAA7146_CAPTURE_BUFFERS ; 
 int max_memory ; 

__attribute__((used)) static int buffer_setup(struct videobuf_queue *q, unsigned int *count, unsigned int *size)
{
	struct file *file = q->priv_data;
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_vv *vv = fh->dev->vv_data;

	if (0 == *count || *count > MAX_SAA7146_CAPTURE_BUFFERS)
		*count = MAX_SAA7146_CAPTURE_BUFFERS;

	*size = vv->video_fmt.sizeimage;

	/* check if we exceed the "max_memory" parameter */
	if( (*count * *size) > (max_memory*1048576) ) {
		*count = (max_memory*1048576) / *size;
	}

	DEB_CAP("%d buffers, %d bytes each\n", *count, *size);

	return 0;
}