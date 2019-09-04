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
struct cvmx_boot_vector_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VECTOR_TABLE_SIZE ; 
 int /*<<< orphan*/  cvmx_boot_vector_init ; 
 struct cvmx_boot_vector_element* cvmx_bootmem_alloc_named_range_once (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int,char*,int /*<<< orphan*/ ) ; 

struct cvmx_boot_vector_element *cvmx_boot_vector_get(void)
{
	struct cvmx_boot_vector_element *ret;

	ret = cvmx_bootmem_alloc_named_range_once(VECTOR_TABLE_SIZE, 0,
		(1ull << 32) - 1, 8, "__boot_vector1__", cvmx_boot_vector_init);
	return ret;
}