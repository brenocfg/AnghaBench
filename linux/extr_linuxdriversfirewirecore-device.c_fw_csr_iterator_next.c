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
struct fw_csr_iterator {int* p; int /*<<< orphan*/  end; } ;

/* Variables and functions */

int fw_csr_iterator_next(struct fw_csr_iterator *ci, int *key, int *value)
{
	*key = *ci->p >> 24;
	*value = *ci->p & 0xffffff;

	return ci->p++ < ci->end;
}