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
struct intel_context {int dummy; } ;

/* Variables and functions */
 int intel_context_active_acquire (struct intel_context*) ; 

__attribute__((used)) static int mock_context_pin(struct intel_context *ce)
{
	return intel_context_active_acquire(ce);
}