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
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 unsigned int EFX_BUF_SIZE ; 

__attribute__((used)) static bool bad_buf_count(unsigned buf_count, unsigned max_entry_count)
{
	unsigned max_buf_count = max_entry_count *
		sizeof(efx_qword_t) / EFX_BUF_SIZE;

	return ((buf_count & (buf_count - 1)) || buf_count > max_buf_count);
}