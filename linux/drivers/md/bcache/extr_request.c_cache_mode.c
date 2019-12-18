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
struct cached_dev {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 unsigned int BDEV_CACHE_MODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int cache_mode(struct cached_dev *dc)
{
	return BDEV_CACHE_MODE(&dc->sb);
}