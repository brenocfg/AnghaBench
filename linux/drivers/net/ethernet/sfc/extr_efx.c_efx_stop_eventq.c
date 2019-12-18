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
struct efx_channel {int enabled; int /*<<< orphan*/  napi_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

void efx_stop_eventq(struct efx_channel *channel)
{
	if (!channel->enabled)
		return;

	napi_disable(&channel->napi_str);
	channel->enabled = false;
}