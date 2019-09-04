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
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DBG (char*,size_t) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  _trng_hwrng_read (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int trng_hwrng_read(struct hwrng *rng, void *data, size_t max, bool wait)
{
	size_t len = max <= PAGE_SIZE ? max : PAGE_SIZE;

	_trng_hwrng_read((u8 *) data, len);

	DEBUG_DBG("trng_hwrng_read()=%zu\n", len);

	return len;
}