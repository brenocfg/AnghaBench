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
struct dm_verity {int ahash_reqsize; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *verity_io_real_digest(struct dm_verity *v,
					struct dm_verity_io *io)
{
	return (u8 *)(io + 1) + v->ahash_reqsize;
}