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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  crc64_be (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static inline uint64_t bch_crc64_update(uint64_t crc,
					const void *p,
					size_t len)
{
	crc = crc64_be(crc, p, len);
	return crc;
}