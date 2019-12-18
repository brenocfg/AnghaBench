#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  error_if_no_space; } ;
struct pool {TYPE_1__ pf; } ;
typedef  enum pool_mode { ____Placeholder_pool_mode } pool_mode ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_NOSPC ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
#define  PM_FAIL 132 
#define  PM_OUT_OF_DATA_SPACE 131 
#define  PM_OUT_OF_METADATA_SPACE 130 
#define  PM_READ_ONLY 129 
#define  PM_WRITE 128 
 int get_pool_mode (struct pool*) ; 

__attribute__((used)) static blk_status_t should_error_unserviceable_bio(struct pool *pool)
{
	enum pool_mode m = get_pool_mode(pool);

	switch (m) {
	case PM_WRITE:
		/* Shouldn't get here */
		DMERR_LIMIT("bio unserviceable, yet pool is in PM_WRITE mode");
		return BLK_STS_IOERR;

	case PM_OUT_OF_DATA_SPACE:
		return pool->pf.error_if_no_space ? BLK_STS_NOSPC : 0;

	case PM_OUT_OF_METADATA_SPACE:
	case PM_READ_ONLY:
	case PM_FAIL:
		return BLK_STS_IOERR;
	default:
		/* Shouldn't get here */
		DMERR_LIMIT("bio unserviceable, yet pool has an unknown mode");
		return BLK_STS_IOERR;
	}
}