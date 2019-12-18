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
struct TYPE_3__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ sdr; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct airspy {int /*<<< orphan*/  buffersize; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct airspy* video_drvdata (struct file*) ; 

__attribute__((used)) static int airspy_g_fmt_sdr_cap(struct file *file, void *priv,
		struct v4l2_format *f)
{
	struct airspy *s = video_drvdata(file);

	f->fmt.sdr.pixelformat = s->pixelformat;
	f->fmt.sdr.buffersize = s->buffersize;
	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));

	return 0;
}