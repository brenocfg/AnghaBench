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
struct opa_aggregate {int /*<<< orphan*/  err_reqlength; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static inline void set_aggr_error(struct opa_aggregate *ag)
{
	ag->err_reqlength |= cpu_to_be16(0x8000);
}