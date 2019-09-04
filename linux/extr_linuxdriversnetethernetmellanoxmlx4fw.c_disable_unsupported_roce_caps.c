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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long MLX4_FLAG_ROCE_V1_V2 ; 
 int /*<<< orphan*/  MLX4_GET (unsigned long,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_PUT (void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BMME_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_FLAGS_OFFSET ; 

__attribute__((used)) static void disable_unsupported_roce_caps(void *buf)
{
	u32 flags;

	MLX4_GET(flags, buf, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	flags &= ~(1UL << 31);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	MLX4_GET(flags, buf, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	flags &= ~(1UL << 24);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	MLX4_GET(flags, buf, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	flags &= ~(MLX4_FLAG_ROCE_V1_V2);
	MLX4_PUT(buf, flags, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
}