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
 int /*<<< orphan*/  IS_ALIGNED (uintptr_t,int) ; 
 int /*<<< orphan*/  is_vmalloc_addr (void const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool flash_dma_buf_ok(const void *buf)
{
	return buf && !is_vmalloc_addr(buf) &&
		likely(IS_ALIGNED((uintptr_t)buf, 4));
}