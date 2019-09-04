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
typedef  int /*<<< orphan*/  u32 ;
struct mv_cesa_engine {int /*<<< orphan*/  int_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 mv_cesa_get_int_mask(struct mv_cesa_engine *engine)
{
	return engine->int_mask;
}