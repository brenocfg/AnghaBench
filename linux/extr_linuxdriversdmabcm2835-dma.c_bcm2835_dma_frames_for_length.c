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
 size_t DIV_ROUND_UP (size_t,size_t) ; 

__attribute__((used)) static inline size_t bcm2835_dma_frames_for_length(size_t len,
						   size_t max_len)
{
	return DIV_ROUND_UP(len, max_len);
}