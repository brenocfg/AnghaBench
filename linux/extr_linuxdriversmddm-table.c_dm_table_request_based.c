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
struct dm_table {int dummy; } ;

/* Variables and functions */
 int __table_type_request_based (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_get_type (struct dm_table*) ; 

bool dm_table_request_based(struct dm_table *t)
{
	return __table_type_request_based(dm_table_get_type(t));
}