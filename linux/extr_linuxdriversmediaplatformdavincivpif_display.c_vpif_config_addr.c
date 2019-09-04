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
struct common_obj {int /*<<< orphan*/  set_addr; } ;
struct channel_obj {scalar_t__ channel_id; struct common_obj* common; } ;

/* Variables and functions */
 scalar_t__ VPIF_CHANNEL3_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  ch2_set_videobuf_addr ; 
 int /*<<< orphan*/  ch2_set_videobuf_addr_yc_nmux ; 
 int /*<<< orphan*/  ch3_set_videobuf_addr ; 

__attribute__((used)) static void vpif_config_addr(struct channel_obj *ch, int muxmode)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	if (VPIF_CHANNEL3_VIDEO == ch->channel_id) {
		common->set_addr = ch3_set_videobuf_addr;
	} else {
		if (2 == muxmode)
			common->set_addr = ch2_set_videobuf_addr_yc_nmux;
		else
			common->set_addr = ch2_set_videobuf_addr;
	}
}