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

/* Variables and functions */
 int COLUMN_INDEX_10BPC ; 
 int COLUMN_INDEX_12BPC ; 
 int COLUMN_INDEX_14BPC ; 
 int COLUMN_INDEX_16BPC ; 
 int COLUMN_INDEX_8BPC ; 
 int EINVAL ; 

__attribute__((used)) static int get_column_index_for_rc_params(u8 bits_per_component)
{
	switch (bits_per_component) {
	case 8:
		return COLUMN_INDEX_8BPC;
	case 10:
		return COLUMN_INDEX_10BPC;
	case 12:
		return COLUMN_INDEX_12BPC;
	case 14:
		return COLUMN_INDEX_14BPC;
	case 16:
		return COLUMN_INDEX_16BPC;
	default:
		return -EINVAL;
	}
}