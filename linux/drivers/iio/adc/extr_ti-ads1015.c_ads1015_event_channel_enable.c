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
struct ads1015_data {int event_channel; int comp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads1015_event_channel_enabled (struct ads1015_data*) ; 

__attribute__((used)) static void ads1015_event_channel_enable(struct ads1015_data *data, int chan,
					 int comp_mode)
{
	WARN_ON(ads1015_event_channel_enabled(data));

	data->event_channel = chan;
	data->comp_mode = comp_mode;
}