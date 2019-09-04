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
typedef  int /*<<< orphan*/  u32 ;
struct hash_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int HASH_BYTES_PER_WORD ; 
 int /*<<< orphan*/  HASH_CLEAR_BITS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_SET_DIN (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  HASH_STR_NBLW_MASK ; 

__attribute__((used)) static void hash_processblock(struct hash_device_data *device_data,
			      const u32 *message, int length)
{
	int len = length / HASH_BYTES_PER_WORD;
	/*
	 * NBLW bits. Reset the number of bits in last word (NBLW).
	 */
	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);

	/*
	 * Write message data to the HASH_DIN register.
	 */
	HASH_SET_DIN(message, len);
}