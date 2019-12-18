#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_10__ {TYPE_4__* s; TYPE_3__* w; TYPE_2__* hw; TYPE_1__* b; } ;
struct wilc {TYPE_5__ cfg; } ;
struct TYPE_9__ {scalar_t__ id; int /*<<< orphan*/ * str; } ;
struct TYPE_8__ {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct TYPE_7__ {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 scalar_t__ CFG_BYTE_CMD ; 
 scalar_t__ CFG_HWORD_CMD ; 
 scalar_t__ CFG_STR_CMD ; 
 scalar_t__ CFG_WORD_CMD ; 
 scalar_t__ WID_NIL ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int wilc_wlan_cfg_get_val(struct wilc *wl, u16 wid, u8 *buffer,
			  u32 buffer_size)
{
	u32 type = (wid >> 12) & 0xf;
	int i, ret = 0;

	i = 0;
	if (type == CFG_BYTE_CMD) {
		do {
			if (wl->cfg.b[i].id == WID_NIL)
				break;

			if (wl->cfg.b[i].id == wid) {
				memcpy(buffer, &wl->cfg.b[i].val, 1);
				ret = 1;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_HWORD_CMD) {
		do {
			if (wl->cfg.hw[i].id == WID_NIL)
				break;

			if (wl->cfg.hw[i].id == wid) {
				memcpy(buffer, &wl->cfg.hw[i].val, 2);
				ret = 2;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_WORD_CMD) {
		do {
			if (wl->cfg.w[i].id == WID_NIL)
				break;

			if (wl->cfg.w[i].id == wid) {
				memcpy(buffer, &wl->cfg.w[i].val, 4);
				ret = 4;
				break;
			}
			i++;
		} while (1);
	} else if (type == CFG_STR_CMD) {
		do {
			u32 id = wl->cfg.s[i].id;

			if (id == WID_NIL)
				break;

			if (id == wid) {
				u16 size = get_unaligned_le16(wl->cfg.s[i].str);

				if (buffer_size >= size) {
					memcpy(buffer, &wl->cfg.s[i].str[2],
					       size);
					ret = size;
				}
				break;
			}
			i++;
		} while (1);
	}
	return ret;
}