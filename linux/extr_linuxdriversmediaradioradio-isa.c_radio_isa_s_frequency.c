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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_frequency {scalar_t__ tuner; scalar_t__ type; int /*<<< orphan*/  frequency; } ;
struct radio_isa_card {int /*<<< orphan*/  freq; TYPE_2__* drv; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* s_frequency ) (struct radio_isa_card*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREQ_HIGH ; 
 int /*<<< orphan*/  FREQ_LOW ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct radio_isa_card*,int /*<<< orphan*/ ) ; 
 struct radio_isa_card* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_isa_s_frequency(struct file *file, void *priv,
				const struct v4l2_frequency *f)
{
	struct radio_isa_card *isa = video_drvdata(file);
	u32 freq = f->frequency;
	int res;

	if (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		return -EINVAL;
	freq = clamp(freq, FREQ_LOW, FREQ_HIGH);
	res = isa->drv->ops->s_frequency(isa, freq);
	if (res == 0)
		isa->freq = freq;
	return res;
}