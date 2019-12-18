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
struct TYPE_2__ {void* direction; } ;
struct most_channel {TYPE_1__ cfg; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENODEV ; 
 void* MOST_CH_RX ; 
 void* MOST_CH_TX ; 
 struct most_channel* get_channel (char*,char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int most_set_cfg_direction(char *mdev, char *mdev_ch, char *buf)
{
	struct most_channel *c = get_channel(mdev, mdev_ch);

	if (!c)
		return -ENODEV;
	if (!strcmp(buf, "dir_rx\n")) {
		c->cfg.direction = MOST_CH_RX;
	} else if (!strcmp(buf, "rx\n")) {
		c->cfg.direction = MOST_CH_RX;
	} else if (!strcmp(buf, "dir_tx\n")) {
		c->cfg.direction = MOST_CH_TX;
	} else if (!strcmp(buf, "tx\n")) {
		c->cfg.direction = MOST_CH_TX;
	} else {
		pr_info("Invalid direction\n");
		return -ENODATA;
	}
	return 0;
}