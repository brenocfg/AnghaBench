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

/* Variables and functions */
 int DRBD_MAX_BATCH_BIO_SIZE ; 
 scalar_t__ IS_ALIGNED (int,int) ; 

__attribute__((used)) static bool plausible_request_size(int size)
{
	return size > 0
		&& size <= DRBD_MAX_BATCH_BIO_SIZE
		&& IS_ALIGNED(size, 512);
}