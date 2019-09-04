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
struct shash_desc {int dummy; } ;
typedef  int /*<<< orphan*/  sha1_block_fn ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_base_do_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ sha1_block_data_order ; 
 int sha1_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

int sha1_finup_arm(struct shash_desc *desc, const u8 *data,
		   unsigned int len, u8 *out)
{
	sha1_base_do_update(desc, data, len,
			    (sha1_block_fn *)sha1_block_data_order);
	return sha1_final(desc, out);
}