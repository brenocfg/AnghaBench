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
#define  G4X_WM_LEVEL_HPLL 129 
#define  G4X_WM_LEVEL_SR 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static int g4x_fbc_fifo_size(int level)
{
	switch (level) {
	case G4X_WM_LEVEL_SR:
		return 7;
	case G4X_WM_LEVEL_HPLL:
		return 15;
	default:
		MISSING_CASE(level);
		return 0;
	}
}