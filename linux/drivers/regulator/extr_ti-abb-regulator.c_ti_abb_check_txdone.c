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
struct ti_abb {int txdone_mask; int /*<<< orphan*/  int_base; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ti_abb_check_txdone(const struct ti_abb *abb)
{
	return !!(readl(abb->int_base) & abb->txdone_mask);
}