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
struct intel_rotation_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline void assert_intel_rotation_info_is_packed(void)
{
	BUILD_BUG_ON(sizeof(struct intel_rotation_info) != 8*sizeof(unsigned int));
}