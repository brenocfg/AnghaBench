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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ u32 ;
struct nct7904_data {int vsen_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 scalar_t__ hwmon_in_input ; 
 int* nct7904_chan_to_index ; 

__attribute__((used)) static umode_t nct7904_in_is_visible(const void *_data, u32 attr, int channel)
{
	const struct nct7904_data *data = _data;
	int index = nct7904_chan_to_index[channel];

	if (channel > 0 && attr == hwmon_in_input &&
	    (data->vsen_mask & BIT(index)))
		return S_IRUGO;

	return 0;
}