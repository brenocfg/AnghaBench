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
struct rocker_wait {int dummy; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int rocker_dma_test_offset (struct rocker const*,struct rocker_wait*,int) ; 

__attribute__((used)) static int rocker_dma_test(const struct rocker *rocker,
			   struct rocker_wait *wait)
{
	int i;
	int err;

	for (i = 0; i < 8; i++) {
		err = rocker_dma_test_offset(rocker, wait, i);
		if (err)
			return err;
	}
	return 0;
}