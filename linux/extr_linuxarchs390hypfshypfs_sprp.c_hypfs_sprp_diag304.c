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
 int /*<<< orphan*/  DIAG_STAT_X304 ; 
 unsigned long __hypfs_sprp_diag304 (void*,unsigned long) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long hypfs_sprp_diag304(void *data, unsigned long cmd)
{
	diag_stat_inc(DIAG_STAT_X304);
	return __hypfs_sprp_diag304(data, cmd);
}