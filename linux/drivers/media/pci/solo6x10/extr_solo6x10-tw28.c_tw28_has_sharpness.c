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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int is_tw286x (struct solo_dev*,int) ; 

bool tw28_has_sharpness(struct solo_dev *solo_dev, u8 ch)
{
	return is_tw286x(solo_dev, ch / 4);
}