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
struct kxtj9_data {int shift; int ctrl_reg1; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KXTJ9_G_2G 130 
#define  KXTJ9_G_4G 129 
#define  KXTJ9_G_8G 128 

__attribute__((used)) static int kxtj9_update_g_range(struct kxtj9_data *tj9, u8 new_g_range)
{
	switch (new_g_range) {
	case KXTJ9_G_2G:
		tj9->shift = 4;
		break;
	case KXTJ9_G_4G:
		tj9->shift = 3;
		break;
	case KXTJ9_G_8G:
		tj9->shift = 2;
		break;
	default:
		return -EINVAL;
	}

	tj9->ctrl_reg1 &= 0xe7;
	tj9->ctrl_reg1 |= new_g_range;

	return 0;
}