#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdt_resource {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_model; int /*<<< orphan*/  x86; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool rdt_get_mb_table(struct rdt_resource *r)
{
	/*
	 * There are no Intel SKUs as of now to support non-linear delay.
	 */
	pr_info("MBA b/w map not implemented for cpu:%d, model:%d",
		boot_cpu_data.x86, boot_cpu_data.x86_model);

	return false;
}