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
struct ad_sigma_delta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_sd_set_comm (struct ad_sigma_delta*,unsigned int) ; 

__attribute__((used)) static int ad7791_set_channel(struct ad_sigma_delta *sd, unsigned int channel)
{
	ad_sd_set_comm(sd, channel);

	return 0;
}