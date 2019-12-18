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
struct efx_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_CHANNEL_MAGIC_TEST (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_farch_magic_event (struct efx_channel*,int /*<<< orphan*/ ) ; 

void efx_farch_ev_test_generate(struct efx_channel *channel)
{
	efx_farch_magic_event(channel, EFX_CHANNEL_MAGIC_TEST(channel));
}