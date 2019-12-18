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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
 int EINVAL ; 

__attribute__((used)) static int dec_ref_count(void *context, uint32_t old, uint32_t *new)
{
	if (!old) {
		DMERR_LIMIT("unable to decrement a reference count below 0");
		return -EINVAL;
	}

	*new = old - 1;
	return 0;
}