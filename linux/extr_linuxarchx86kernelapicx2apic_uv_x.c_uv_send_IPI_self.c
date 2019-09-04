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
 int /*<<< orphan*/  APIC_SELF_IPI ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uv_send_IPI_self(int vector)
{
	apic_write(APIC_SELF_IPI, vector);
}