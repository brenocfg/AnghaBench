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
struct block_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ bch_is_open_backing (struct block_device*) ; 
 scalar_t__ bch_is_open_cache (struct block_device*) ; 

__attribute__((used)) static bool bch_is_open(struct block_device *bdev)
{
	return bch_is_open_cache(bdev) || bch_is_open_backing(bdev);
}