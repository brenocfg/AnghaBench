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
struct d0_locking_features {int supported_features; } ;

/* Variables and functions */
 int MBR_ENABLED_MASK ; 

__attribute__((used)) static bool check_mbrenabled(const void *data)
{
	const struct d0_locking_features *lfeat = data;
	u8 sup_feat = lfeat->supported_features;

	return !!(sup_feat & MBR_ENABLED_MASK);
}