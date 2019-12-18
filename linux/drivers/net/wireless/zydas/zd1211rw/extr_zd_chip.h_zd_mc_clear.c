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
struct zd_mc_hash {int high; scalar_t__ low; } ;

/* Variables and functions */

__attribute__((used)) static inline void zd_mc_clear(struct zd_mc_hash *hash)
{
	hash->low = 0;
	/* The interfaces must always received broadcasts.
	 * The hash of the broadcast address ff:ff:ff:ff:ff:ff is 63.
	 */
	hash->high = 0x80000000;
}