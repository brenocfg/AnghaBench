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
struct max197_data {int* ctrl_bytes; } ;

/* Variables and functions */
 int MAX197_RNG ; 

__attribute__((used)) static inline bool max197_is_full_range(struct max197_data *data, int channel)
{
	return data->ctrl_bytes[channel] & MAX197_RNG;
}