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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void get_64bit_val(u64 *wqe_words, u32 byte_index, u64 *value)
{
	*value = wqe_words[byte_index >> 3];
}