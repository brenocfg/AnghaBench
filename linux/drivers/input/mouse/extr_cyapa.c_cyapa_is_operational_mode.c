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
 scalar_t__ CYAPA_STATE_OP ; 
 scalar_t__ cyapa_is_pip_app_mode (struct cyapa*) ; 

__attribute__((used)) static inline bool cyapa_is_operational_mode(struct cyapa *cyapa)
{
	if (cyapa_is_pip_app_mode(cyapa))
		return true;

	if (cyapa->gen == CYAPA_GEN3 && cyapa->state == CYAPA_STATE_OP)
		return true;

	return false;
}