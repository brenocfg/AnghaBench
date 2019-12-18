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
struct dm_verity_io {int dummy; } ;
struct dm_verity {int dummy; } ;
struct bvec_iter {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum verity_block_type { ____Placeholder_verity_block_type } verity_block_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int verity_fec_decode(struct dm_verity *v,
				    struct dm_verity_io *io,
				    enum verity_block_type type,
				    sector_t block, u8 *dest,
				    struct bvec_iter *iter)
{
	return -EOPNOTSUPP;
}