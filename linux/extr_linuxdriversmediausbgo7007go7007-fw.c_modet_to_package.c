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
typedef  int u16 ;
struct go7007 {int* modet_map; TYPE_1__* modet; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int enable; int pixel_threshold; int motion_threshold; int mb_threshold; } ;

/* Variables and functions */
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int modet_to_package(struct go7007 *go, __le16 *code, int space)
{
	bool has_modet0 = go->modet[0].enable;
	bool has_modet1 = go->modet[1].enable;
	bool has_modet2 = go->modet[2].enable;
	bool has_modet3 = go->modet[3].enable;
	int ret, mb, i, addr, cnt = 0;
	u16 pack[32];
	u16 thresholds[] = {
		0x200e,		0,
		0xbf82,		has_modet0 ? go->modet[0].pixel_threshold : 32767,
		0xbf83,		has_modet1 ? go->modet[1].pixel_threshold : 32767,
		0xbf84,		has_modet2 ? go->modet[2].pixel_threshold : 32767,
		0xbf85,		has_modet3 ? go->modet[3].pixel_threshold : 32767,
		0xbf86,		has_modet0 ? go->modet[0].motion_threshold : 32767,
		0xbf87,		has_modet1 ? go->modet[1].motion_threshold : 32767,
		0xbf88,		has_modet2 ? go->modet[2].motion_threshold : 32767,
		0xbf89,		has_modet3 ? go->modet[3].motion_threshold : 32767,
		0xbf8a,		has_modet0 ? go->modet[0].mb_threshold : 32767,
		0xbf8b,		has_modet1 ? go->modet[1].mb_threshold : 32767,
		0xbf8c,		has_modet2 ? go->modet[2].mb_threshold : 32767,
		0xbf8d,		has_modet3 ? go->modet[3].mb_threshold : 32767,
		0xbf8e,		0,
		0xbf8f,		0,
		0,		0,
	};

	ret = copy_packages(code, thresholds, 1, space);
	if (ret < 0)
		return -1;
	cnt += ret;

	addr = 0xbac0;
	memset(pack, 0, 64);
	i = 0;
	for (mb = 0; mb < 1624; ++mb) {
		pack[i * 2 + 3] <<= 2;
		pack[i * 2 + 3] |= go->modet_map[mb];
		if (mb % 8 != 7)
			continue;
		pack[i * 2 + 2] = addr++;
		++i;
		if (i == 10 || mb == 1623) {
			pack[0] = 0x2000 | i;
			ret = copy_packages(code + cnt, pack, 1, space - cnt);
			if (ret < 0)
				return -1;
			cnt += ret;
			i = 0;
			memset(pack, 0, 64);
		}
		pack[i * 2 + 3] = 0;
	}

	memset(pack, 0, 64);
	i = 0;
	for (addr = 0xbb90; addr < 0xbbfa; ++addr) {
		pack[i * 2 + 2] = addr;
		pack[i * 2 + 3] = 0;
		++i;
		if (i == 10 || addr == 0xbbf9) {
			pack[0] = 0x2000 | i;
			ret = copy_packages(code + cnt, pack, 1, space - cnt);
			if (ret < 0)
				return -1;
			cnt += ret;
			i = 0;
			memset(pack, 0, 64);
		}
	}
	return cnt;
}