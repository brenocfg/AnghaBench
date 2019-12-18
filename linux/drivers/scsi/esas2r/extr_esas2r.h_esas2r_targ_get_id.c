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
typedef  int /*<<< orphan*/  u16 ;
struct esas2r_target {int dummy; } ;
struct esas2r_adapter {struct esas2r_target* targetdb; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 esas2r_targ_get_id(struct esas2r_target *t,
				     struct esas2r_adapter *a)
{
	return (u16)(uintptr_t)(t - a->targetdb);
}