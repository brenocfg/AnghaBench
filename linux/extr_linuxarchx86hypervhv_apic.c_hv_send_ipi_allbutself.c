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

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  hv_send_ipi_mask_allbutself (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hv_send_ipi_allbutself(int vector)
{
	hv_send_ipi_mask_allbutself(cpu_online_mask, vector);
}