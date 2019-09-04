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
struct cyapa {scalar_t__ gen; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CYAPA_GEN3 ; 
 scalar_t__ CYAPA_STATE_BL_ACTIVE ; 
 scalar_t__ CYAPA_STATE_BL_BUSY ; 
 scalar_t__ cyapa_is_pip_bl_mode (struct cyapa*) ; 

__attribute__((used)) static bool cyapa_is_bootloader_mode(struct cyapa *cyapa)
{
	if (cyapa_is_pip_bl_mode(cyapa))
		return true;

	if (cyapa->gen == CYAPA_GEN3 &&
		cyapa->state >= CYAPA_STATE_BL_BUSY &&
		cyapa->state <= CYAPA_STATE_BL_ACTIVE)
		return true;

	return false;
}