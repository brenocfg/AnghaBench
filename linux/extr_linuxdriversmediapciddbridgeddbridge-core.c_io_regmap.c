#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddb_regmap {int dummy; } ;
struct ddb_io {TYPE_3__* port; } ;
struct ddb_info {struct ddb_regmap const* regmap; } ;
struct TYPE_6__ {size_t lnr; TYPE_2__* dev; } ;
struct TYPE_5__ {TYPE_1__* link; } ;
struct TYPE_4__ {struct ddb_info* info; } ;

/* Variables and functions */

__attribute__((used)) static const struct ddb_regmap *io_regmap(struct ddb_io *io, int link)
{
	const struct ddb_info *info;

	if (link)
		info = io->port->dev->link[io->port->lnr].info;
	else
		info = io->port->dev->link[0].info;

	if (!info)
		return NULL;

	return info->regmap;
}