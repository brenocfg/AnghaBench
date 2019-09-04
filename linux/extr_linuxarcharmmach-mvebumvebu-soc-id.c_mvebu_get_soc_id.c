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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ is_id_valid ; 
 int /*<<< orphan*/  soc_dev_id ; 
 int /*<<< orphan*/  soc_rev ; 

int mvebu_get_soc_id(u32 *dev, u32 *rev)
{
	if (is_id_valid) {
		*dev = soc_dev_id;
		*rev = soc_rev;
		return 0;
	} else
		return -ENODEV;
}