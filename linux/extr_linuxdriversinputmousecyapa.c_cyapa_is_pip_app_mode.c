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
 scalar_t__ CYAPA_GEN5 ; 
 scalar_t__ CYAPA_GEN6 ; 
 scalar_t__ CYAPA_STATE_GEN5_APP ; 
 scalar_t__ CYAPA_STATE_GEN6_APP ; 

bool cyapa_is_pip_app_mode(struct cyapa *cyapa)
{
	if (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_APP)
		return true;

	if (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_APP)
		return true;

	return false;
}