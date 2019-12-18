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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dbr_size; } ;
struct most_channel {TYPE_1__ cfg; } ;

/* Variables and functions */
 int ENODEV ; 
 struct most_channel* get_channel (char*,char*) ; 

int most_set_cfg_dbr_size(char *mdev, char *mdev_ch, u16 val)
{
	struct most_channel *c = get_channel(mdev, mdev_ch);

	if (!c)
		return -ENODEV;
	c->cfg.dbr_size = val;
	return 0;
}