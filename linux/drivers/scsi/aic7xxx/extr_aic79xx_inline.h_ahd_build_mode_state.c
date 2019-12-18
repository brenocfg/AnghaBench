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
struct ahd_softc {int dummy; } ;
typedef  int ahd_mode_state ;
typedef  int ahd_mode ;

/* Variables and functions */
 int DST_MODE_SHIFT ; 
 int SRC_MODE_SHIFT ; 

__attribute__((used)) static inline ahd_mode_state
ahd_build_mode_state(struct ahd_softc *ahd, ahd_mode src, ahd_mode dst)
{
	return ((src << SRC_MODE_SHIFT) | (dst << DST_MODE_SHIFT));
}