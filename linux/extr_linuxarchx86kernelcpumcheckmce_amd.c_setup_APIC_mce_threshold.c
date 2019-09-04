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
 int /*<<< orphan*/  APIC_EILVT_MSG_FIX ; 
 int /*<<< orphan*/  THRESHOLD_APIC_VECTOR ; 
 int /*<<< orphan*/  setup_APIC_eilvt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_APIC_mce_threshold(int reserved, int new)
{
	if (reserved < 0 && !setup_APIC_eilvt(new, THRESHOLD_APIC_VECTOR,
					      APIC_EILVT_MSG_FIX, 0))
		return new;

	return reserved;
}