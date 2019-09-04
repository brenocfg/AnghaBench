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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  _MDFLD_PIPEC_VBLANK_FLAG ; 
 int /*<<< orphan*/  _PSB_VSYNC_PIPEA_FLAG ; 
 int /*<<< orphan*/  _PSB_VSYNC_PIPEB_FLAG ; 

__attribute__((used)) static inline u32
mid_pipe_vsync(int pipe)
{
	if (pipe == 0)
		return _PSB_VSYNC_PIPEA_FLAG;
	if (pipe == 1)
		return _PSB_VSYNC_PIPEB_FLAG;
	if (pipe == 2)
		return _MDFLD_PIPEC_VBLANK_FLAG;
	BUG();
}