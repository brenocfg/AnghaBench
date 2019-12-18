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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 tlan_hash_func(const u8 *a)
{
	u8     hash;

	hash = (a[0]^a[3]);		/* & 077 */
	hash ^= ((a[0]^a[3])>>6);	/* & 003 */
	hash ^= ((a[1]^a[4])<<2);	/* & 074 */
	hash ^= ((a[1]^a[4])>>4);	/* & 017 */
	hash ^= ((a[2]^a[5])<<4);	/* & 060 */
	hash ^= ((a[2]^a[5])>>2);	/* & 077 */

	return hash & 077;
}