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
struct ad7791_state {int /*<<< orphan*/  mode; int /*<<< orphan*/  sd; TYPE_1__* info; int /*<<< orphan*/  filter; } ;
struct ad7791_platform_data {scalar_t__ unipolar; scalar_t__ burnout_current; int /*<<< orphan*/  buffered; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7791_FILTER_RATE_16_6 ; 
 int AD7791_FLAG_HAS_BUFFER ; 
 int AD7791_FLAG_HAS_BURNOUT ; 
 int AD7791_FLAG_HAS_UNIPOLAR ; 
 int /*<<< orphan*/  AD7791_MODE_BUFFER ; 
 int /*<<< orphan*/  AD7791_MODE_BURNOUT ; 
 int /*<<< orphan*/  AD7791_MODE_UNIPOLAR ; 
 int /*<<< orphan*/  AD7791_REG_MODE ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7791_setup(struct ad7791_state *st,
			struct ad7791_platform_data *pdata)
{
	/* Set to poweron-reset default values */
	st->mode = AD7791_MODE_BUFFER;
	st->filter = AD7791_FILTER_RATE_16_6;

	if (!pdata)
		return 0;

	if ((st->info->flags & AD7791_FLAG_HAS_BUFFER) && !pdata->buffered)
		st->mode &= ~AD7791_MODE_BUFFER;

	if ((st->info->flags & AD7791_FLAG_HAS_BURNOUT) &&
		pdata->burnout_current)
		st->mode |= AD7791_MODE_BURNOUT;

	if ((st->info->flags & AD7791_FLAG_HAS_UNIPOLAR) && pdata->unipolar)
		st->mode |= AD7791_MODE_UNIPOLAR;

	return ad_sd_write_reg(&st->sd, AD7791_REG_MODE, sizeof(st->mode),
		st->mode);
}