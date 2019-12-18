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
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_free_q_vectors (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset_interrupt_capability (struct igb_adapter*) ; 

__attribute__((used)) static void igb_clear_interrupt_scheme(struct igb_adapter *adapter)
{
	igb_free_q_vectors(adapter);
	igb_reset_interrupt_capability(adapter);
}