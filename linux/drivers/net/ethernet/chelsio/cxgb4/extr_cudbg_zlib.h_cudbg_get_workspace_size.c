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
 int /*<<< orphan*/  CUDBG_ZLIB_MEM_LVL ; 
 int /*<<< orphan*/  CUDBG_ZLIB_WIN_BITS ; 
 int zlib_deflate_workspacesize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cudbg_get_workspace_size(void)
{
	return zlib_deflate_workspacesize(CUDBG_ZLIB_WIN_BITS,
					  CUDBG_ZLIB_MEM_LVL);
}