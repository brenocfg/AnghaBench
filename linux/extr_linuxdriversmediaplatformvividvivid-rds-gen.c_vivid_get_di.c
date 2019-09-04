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
typedef  int u8 ;
struct vivid_rds_gen {int dyn_pty; int compressed; int art_head; int mono_stereo; } ;

/* Variables and functions */

__attribute__((used)) static u8 vivid_get_di(const struct vivid_rds_gen *rds, unsigned grp)
{
	switch (grp) {
	case 0:
		return (rds->dyn_pty << 2) | (grp & 3);
	case 1:
		return (rds->compressed << 2) | (grp & 3);
	case 2:
		return (rds->art_head << 2) | (grp & 3);
	case 3:
		return (rds->mono_stereo << 2) | (grp & 3);
	}
	return 0;
}