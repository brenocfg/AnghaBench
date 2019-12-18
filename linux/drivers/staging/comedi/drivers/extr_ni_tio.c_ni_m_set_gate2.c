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
struct ni_gpct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ni_tio_set_gate2_raw (struct ni_gpct*,unsigned int) ; 

__attribute__((used)) static int ni_m_set_gate2(struct ni_gpct *counter, unsigned int gate_source)
{
	/*
	 * FIXME: We don't know what the m-series second gate codes are,
	 * so we'll just pass the bits through for now.
	 */
	ni_tio_set_gate2_raw(counter, gate_source);
	return 0;
}