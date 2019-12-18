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

__attribute__((used)) static int ni_m_gate2_to_generic_gate(unsigned int gate, unsigned int *src)
{
	/*
	 * FIXME: the second gate sources for the m series are undocumented,
	 * so we just return the raw bits for now.
	 */
	*src = gate;
	return 0;
}