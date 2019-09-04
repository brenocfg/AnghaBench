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
struct intel_uncore_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uncore_type_exit (struct intel_uncore_type*) ; 

__attribute__((used)) static void uncore_types_exit(struct intel_uncore_type **types)
{
	for (; *types; types++)
		uncore_type_exit(*types);
}