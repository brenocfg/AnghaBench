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
struct sd {int /*<<< orphan*/ * sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov9650_stop (struct sd*) ; 

void ov9650_disconnect(struct sd *sd)
{
	ov9650_stop(sd);

	sd->sensor = NULL;
}