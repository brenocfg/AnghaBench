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
typedef  int /*<<< orphan*/  u32 ;
struct l2t_data {int l2t_size; } ;

/* Variables and functions */
 unsigned int jhash_2words (int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int arp_hash(struct l2t_data *d, const u32 *key,
				    int ifindex)
{
	unsigned int l2t_size_half = d->l2t_size / 2;

	return jhash_2words(*key, ifindex, 0) % l2t_size_half;
}