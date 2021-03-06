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
struct ad7192_state {int /*<<< orphan*/  mode; int /*<<< orphan*/  sd; } ;
typedef  enum ad_sigma_delta_mode { ____Placeholder_ad_sigma_delta_mode } ad_sigma_delta_mode ;

/* Variables and functions */
 int /*<<< orphan*/  AD7192_MODE_SEL (int) ; 
 int /*<<< orphan*/  AD7192_MODE_SEL_MASK ; 
 int /*<<< orphan*/  AD7192_REG_MODE ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ad7192_state* ad_sigma_delta_to_ad7192 (struct ad_sigma_delta*) ; 

__attribute__((used)) static int ad7192_set_mode(struct ad_sigma_delta *sd,
			   enum ad_sigma_delta_mode mode)
{
	struct ad7192_state *st = ad_sigma_delta_to_ad7192(sd);

	st->mode &= ~AD7192_MODE_SEL_MASK;
	st->mode |= AD7192_MODE_SEL(mode);

	return ad_sd_write_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
}