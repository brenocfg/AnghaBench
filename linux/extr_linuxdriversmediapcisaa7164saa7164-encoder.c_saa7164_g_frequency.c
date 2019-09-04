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
struct v4l2_frequency {int /*<<< orphan*/  frequency; scalar_t__ tuner; } ;
struct saa7164_port {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int EINVAL ; 

int saa7164_g_frequency(struct saa7164_port *port, struct v4l2_frequency *f)
{
	if (f->tuner)
		return -EINVAL;

	f->frequency = port->freq;
	return 0;
}