#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data_type; } ;
struct most_channel {TYPE_1__ cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  most_ch_data_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENODEV ; 
 TYPE_2__* ch_data_type ; 
 struct most_channel* get_channel (char*,char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

int most_set_cfg_datatype(char *mdev, char *mdev_ch, char *buf)
{
	int i;
	struct most_channel *c = get_channel(mdev, mdev_ch);

	if (!c)
		return -ENODEV;
	for (i = 0; i < ARRAY_SIZE(ch_data_type); i++) {
		if (!strcmp(buf, ch_data_type[i].name)) {
			c->cfg.data_type = ch_data_type[i].most_ch_data_type;
			break;
		}
	}

	if (i == ARRAY_SIZE(ch_data_type))
		pr_info("WARN: invalid attribute settings\n");
	return 0;
}