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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ DESC_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_TYPE_MASK ; 
 int /*<<< orphan*/  DESC_TYPE_SHIFT ; 
 scalar_t__ NPTR_TYPE ; 
 int /*<<< orphan*/  flexrm_read_desc (void*) ; 

__attribute__((used)) static bool flexrm_is_next_table_desc(void *desc_ptr)
{
	u64 desc = flexrm_read_desc(desc_ptr);
	u32 type = DESC_DEC(desc, DESC_TYPE_SHIFT, DESC_TYPE_MASK);

	return (type == NPTR_TYPE) ? true : false;
}