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
typedef  int /*<<< orphan*/  v2_le ;
typedef  int /*<<< orphan*/  v1_le ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  unpack_block_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int data_block_equal(void *context, const void *value1_le, const void *value2_le)
{
	__le64 v1_le, v2_le;
	uint64_t b1, b2;
	uint32_t t;

	memcpy(&v1_le, value1_le, sizeof(v1_le));
	memcpy(&v2_le, value2_le, sizeof(v2_le));
	unpack_block_time(le64_to_cpu(v1_le), &b1, &t);
	unpack_block_time(le64_to_cpu(v2_le), &b2, &t);

	return b1 == b2;
}