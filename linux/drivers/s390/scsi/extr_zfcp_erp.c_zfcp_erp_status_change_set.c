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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_erp_status_change_set(unsigned long mask, atomic_t *status)
{
	return (atomic_read(status) ^ mask) & mask;
}