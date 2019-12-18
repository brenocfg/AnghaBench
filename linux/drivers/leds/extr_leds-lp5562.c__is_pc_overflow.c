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
struct lp55xx_predef_pattern {scalar_t__ size_r; scalar_t__ size_g; scalar_t__ size_b; } ;

/* Variables and functions */
 scalar_t__ LP5562_PROGRAM_LENGTH ; 

__attribute__((used)) static inline bool _is_pc_overflow(struct lp55xx_predef_pattern *ptn)
{
	return ptn->size_r >= LP5562_PROGRAM_LENGTH ||
	       ptn->size_g >= LP5562_PROGRAM_LENGTH ||
	       ptn->size_b >= LP5562_PROGRAM_LENGTH;
}