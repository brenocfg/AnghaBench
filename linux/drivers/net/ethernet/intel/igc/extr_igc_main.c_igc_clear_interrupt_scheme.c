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
struct igc_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  igc_free_q_vectors (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset_interrupt_capability (struct igc_adapter*) ; 

__attribute__((used)) static void igc_clear_interrupt_scheme(struct igc_adapter *adapter)
{
	igc_free_q_vectors(adapter);
	igc_reset_interrupt_capability(adapter);
}