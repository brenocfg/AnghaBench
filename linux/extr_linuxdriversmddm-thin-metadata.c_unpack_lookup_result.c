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
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_thin_lookup_result {int /*<<< orphan*/  shared; int /*<<< orphan*/  block; } ;
struct dm_thin_device {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  __snapshotted_since (struct dm_thin_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_block_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unpack_lookup_result(struct dm_thin_device *td, __le64 value,
				 struct dm_thin_lookup_result *result)
{
	uint64_t block_time = 0;
	dm_block_t exception_block;
	uint32_t exception_time;

	block_time = le64_to_cpu(value);
	unpack_block_time(block_time, &exception_block, &exception_time);
	result->block = exception_block;
	result->shared = __snapshotted_since(td, exception_time);
}