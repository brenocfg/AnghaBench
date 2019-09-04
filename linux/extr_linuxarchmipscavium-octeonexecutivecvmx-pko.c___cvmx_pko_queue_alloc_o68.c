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
 int /*<<< orphan*/  __cvmx_pko_iport_config (int) ; 

__attribute__((used)) static void __cvmx_pko_queue_alloc_o68(void)
{
	int port;

	for (port = 0; port < 48; port++)
		__cvmx_pko_iport_config(port);
}