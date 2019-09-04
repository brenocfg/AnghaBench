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
struct videobuf_queue {struct cx231xx_fh* priv_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int width; int height; TYPE_1__* format; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 unsigned int CX231XX_DEF_BUF ; 
 unsigned int CX231XX_MIN_BUF ; 
 int /*<<< orphan*/  cx231xx_enable_analog_tuner (struct cx231xx*) ; 

__attribute__((used)) static int
buffer_setup(struct videobuf_queue *vq, unsigned int *count, unsigned int *size)
{
	struct cx231xx_fh *fh = vq->priv_data;
	struct cx231xx *dev = fh->dev;

	*size = (fh->dev->width * fh->dev->height * dev->format->depth + 7)>>3;
	if (0 == *count)
		*count = CX231XX_DEF_BUF;

	if (*count < CX231XX_MIN_BUF)
		*count = CX231XX_MIN_BUF;


	cx231xx_enable_analog_tuner(dev);

	return 0;
}