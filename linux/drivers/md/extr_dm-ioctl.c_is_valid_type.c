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
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;

/* Variables and functions */
 int DM_TYPE_BIO_BASED ; 
 int DM_TYPE_DAX_BIO_BASED ; 

__attribute__((used)) static bool is_valid_type(enum dm_queue_mode cur, enum dm_queue_mode new)
{
	if (cur == new ||
	    (cur == DM_TYPE_BIO_BASED && new == DM_TYPE_DAX_BIO_BASED))
		return true;

	return false;
}