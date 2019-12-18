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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static inline void inc_wptr(unsigned int *wptr, unsigned int increment_bytes,
				unsigned int buffer_size_bytes)
{
	unsigned int temp = *wptr + increment_bytes / sizeof(uint32_t);

	WARN((temp * sizeof(uint32_t)) > buffer_size_bytes,
	     "Runlist IB overflow");
	*wptr = temp;
}