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
typedef  int /*<<< orphan*/  u8 ;
struct rndis_params {int /*<<< orphan*/  const* host_mac; } ;

/* Variables and functions */

void rndis_set_host_mac(struct rndis_params *params, const u8 *addr)
{
	params->host_mac = addr;
}