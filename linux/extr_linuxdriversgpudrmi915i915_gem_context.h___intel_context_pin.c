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
struct intel_context {int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 

__attribute__((used)) static inline void __intel_context_pin(struct intel_context *ce)
{
	GEM_BUG_ON(!ce->pin_count);
	ce->pin_count++;
}