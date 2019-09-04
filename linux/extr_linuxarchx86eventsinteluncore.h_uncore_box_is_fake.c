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
struct intel_uncore_box {scalar_t__ pkgid; } ;

/* Variables and functions */

__attribute__((used)) static inline bool uncore_box_is_fake(struct intel_uncore_box *box)
{
	return (box->pkgid < 0);
}