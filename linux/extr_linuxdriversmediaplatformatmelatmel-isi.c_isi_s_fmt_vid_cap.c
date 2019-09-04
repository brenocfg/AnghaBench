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
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;
struct atmel_isi {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int isi_set_fmt (struct atmel_isi*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 
 struct atmel_isi* video_drvdata (struct file*) ; 

__attribute__((used)) static int isi_s_fmt_vid_cap(struct file *file, void *priv,
			      struct v4l2_format *f)
{
	struct atmel_isi *isi = video_drvdata(file);

	if (vb2_is_streaming(&isi->queue))
		return -EBUSY;

	return isi_set_fmt(isi, f);
}