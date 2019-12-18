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
typedef  size_t u32 ;
struct ddb_link {struct ddb_info* info; } ;
struct ddb_info {int board_control; int board_control_2; } ;
struct ddb {struct ddb_link* link; } ;

/* Variables and functions */
 int BOARD_CONTROL ; 
 int DDB_LINK_TAG (size_t) ; 
 size_t DDB_MAX_LINK ; 
 int /*<<< orphan*/  ddb_init_tempmon (struct ddb_link*) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ddb_init_boards(struct ddb *dev)
{
	const struct ddb_info *info;
	struct ddb_link *link;
	u32 l;

	for (l = 0; l < DDB_MAX_LINK; l++) {
		link = &dev->link[l];
		info = link->info;

		if (!info)
			continue;
		if (info->board_control) {
			ddbwritel(dev, 0, DDB_LINK_TAG(l) | BOARD_CONTROL);
			msleep(100);
			ddbwritel(dev, info->board_control_2,
				  DDB_LINK_TAG(l) | BOARD_CONTROL);
			usleep_range(2000, 3000);
			ddbwritel(dev,
				  info->board_control_2 | info->board_control,
				  DDB_LINK_TAG(l) | BOARD_CONTROL);
			usleep_range(2000, 3000);
		}
		ddb_init_tempmon(link);
	}
	return 0;
}