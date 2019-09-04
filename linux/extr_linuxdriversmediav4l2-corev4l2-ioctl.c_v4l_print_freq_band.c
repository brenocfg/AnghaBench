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
struct v4l2_frequency_band {int /*<<< orphan*/  modulation; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  capability; int /*<<< orphan*/  index; int /*<<< orphan*/  type; int /*<<< orphan*/  tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_freq_band(const void *arg, bool write_only)
{
	const struct v4l2_frequency_band *p = arg;

	pr_cont("tuner=%u, type=%u, index=%u, capability=0x%x, rangelow=%u, rangehigh=%u, modulation=0x%x\n",
			p->tuner, p->type, p->index,
			p->capability, p->rangelow,
			p->rangehigh, p->modulation);
}