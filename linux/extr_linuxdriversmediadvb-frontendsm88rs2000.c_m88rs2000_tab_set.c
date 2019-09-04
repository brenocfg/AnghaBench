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
struct m88rs2000_state {int dummy; } ;
struct inittab {int cmd; int reg; int val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int m88rs2000_tab_set(struct m88rs2000_state *state,
		struct inittab *tab)
{
	int ret = 0;
	u8 i;
	if (tab == NULL)
		return -EINVAL;

	for (i = 0; i < 255; i++) {
		switch (tab[i].cmd) {
		case 0x01:
			ret = m88rs2000_writereg(state, tab[i].reg,
				tab[i].val);
			break;
		case 0x10:
			if (tab[i].reg > 0)
				mdelay(tab[i].reg);
			break;
		case 0xff:
			if (tab[i].reg == 0xaa && tab[i].val == 0xff)
				return 0;
		case 0x00:
			break;
		default:
			return -EINVAL;
		}
		if (ret < 0)
			return -ENODEV;
	}
	return 0;
}