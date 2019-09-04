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
struct ad7793_state {int /*<<< orphan*/  conf; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7793_CONF_CHAN (unsigned int) ; 
 int /*<<< orphan*/  AD7793_CONF_CHAN_MASK ; 
 int /*<<< orphan*/  AD7793_REG_CONF ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ad7793_state* ad_sigma_delta_to_ad7793 (struct ad_sigma_delta*) ; 

__attribute__((used)) static int ad7793_set_channel(struct ad_sigma_delta *sd, unsigned int channel)
{
	struct ad7793_state *st = ad_sigma_delta_to_ad7793(sd);

	st->conf &= ~AD7793_CONF_CHAN_MASK;
	st->conf |= AD7793_CONF_CHAN(channel);

	return ad_sd_write_reg(&st->sd, AD7793_REG_CONF, 2, st->conf);
}