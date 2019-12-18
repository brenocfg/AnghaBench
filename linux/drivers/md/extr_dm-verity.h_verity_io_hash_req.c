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
struct dm_verity_io {int dummy; } ;
struct dm_verity {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ahash_request *verity_io_hash_req(struct dm_verity *v,
						     struct dm_verity_io *io)
{
	return (struct ahash_request *)(io + 1);
}