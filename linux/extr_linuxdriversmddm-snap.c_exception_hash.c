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
typedef  int uint32_t ;
struct dm_exception_table {int hash_shift; int hash_mask; } ;
typedef  int chunk_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t exception_hash(struct dm_exception_table *et, chunk_t chunk)
{
	return (chunk >> et->hash_shift) & et->hash_mask;
}