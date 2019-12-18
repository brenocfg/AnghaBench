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
struct v4l2_frequency {scalar_t__ tuner; } ;
struct saa7134_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  saa7134_tvaudio_do_scan (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 
 int /*<<< orphan*/  tuner ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

int saa7134_s_frequency(struct file *file, void *priv,
					const struct v4l2_frequency *f)
{
	struct saa7134_dev *dev = video_drvdata(file);

	if (0 != f->tuner)
		return -EINVAL;

	saa_call_all(dev, tuner, s_frequency, f);

	saa7134_tvaudio_do_scan(dev);
	return 0;
}