#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
struct TYPE_3__ {TYPE_2__* b; } ;
struct wilc {TYPE_1__ cfg; } ;
struct TYPE_4__ {scalar_t__ id; void* val; } ;

/* Variables and functions */
 scalar_t__ WID_NIL ; 
 int WID_STATUS ; 
 int get_unaligned_le16 (void**) ; 

__attribute__((used)) static void wilc_wlan_parse_info_frame(struct wilc *wl, u8 *info)
{
	u32 wid, len;

	wid = get_unaligned_le16(info);

	len = info[2];

	if (len == 1 && wid == WID_STATUS) {
		int i = 0;

		do {
			if (wl->cfg.b[i].id == WID_NIL)
				break;

			if (wl->cfg.b[i].id == wid) {
				wl->cfg.b[i].val = info[3];
				break;
			}
			i++;
		} while (1);
	}
}