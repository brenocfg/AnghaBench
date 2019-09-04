#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hash_device_data {TYPE_1__* base; } ;
struct hash_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CLEAR_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_INITIALIZE ; 
 int HASH_STR_DCAL_MASK ; 
 int /*<<< orphan*/  HASH_STR_NBLW_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (int /*<<< orphan*/ *) ; 

void hash_begin(struct hash_device_data *device_data, struct hash_ctx *ctx)
{
	/* HW and SW initializations */
	/* Note: there is no need to initialize buffer and digest members */

	while (readl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	/*
	 * INIT bit. Set this bit to 0b1 to reset the HASH processor core and
	 * prepare the initialize the HASH accelerator to compute the message
	 * digest of a new message.
	 */
	HASH_INITIALIZE;

	/*
	 * NBLW bits. Reset the number of bits in last word (NBLW).
	 */
	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);
}