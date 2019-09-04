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
typedef  struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } const v4l2_frequency ;
struct TYPE_2__ {scalar_t__ tuner_type; } ;
struct cx88_core {int /*<<< orphan*/  freq; TYPE_1__ board; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 
 int /*<<< orphan*/  cx88_newstation (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int cx88_set_freq(struct cx88_core  *core,
		  const struct v4l2_frequency *f)
{
	struct v4l2_frequency new_freq = *f;

	if (unlikely(core->board.tuner_type == UNSET))
		return -EINVAL;
	if (unlikely(f->tuner != 0))
		return -EINVAL;

	cx88_newstation(core);
	call_all(core, tuner, s_frequency, f);
	call_all(core, tuner, g_frequency, &new_freq);
	core->freq = new_freq.frequency;

	/* When changing channels it is required to reset TVAUDIO */
	usleep_range(10000, 20000);
	cx88_set_tvaudio(core);

	return 0;
}