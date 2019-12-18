#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cyapa {int gen; int operational; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* operational_check ) (struct cyapa*) ;} ;

/* Variables and functions */
#define  CYAPA_GEN3 130 
#define  CYAPA_GEN5 129 
#define  CYAPA_GEN6 128 
 int ENODEV ; 
 TYPE_1__ cyapa_gen3_ops ; 
 TYPE_1__ cyapa_gen5_ops ; 
 TYPE_1__ cyapa_gen6_ops ; 
 scalar_t__ cyapa_is_operational_mode (struct cyapa*) ; 
 int cyapa_poll_state (struct cyapa*,int) ; 
 int stub1 (struct cyapa*) ; 

__attribute__((used)) static int cyapa_check_is_operational(struct cyapa *cyapa)
{
	int error;

	error = cyapa_poll_state(cyapa, 4000);
	if (error)
		return error;

	switch (cyapa->gen) {
	case CYAPA_GEN6:
		cyapa->ops = &cyapa_gen6_ops;
		break;
	case CYAPA_GEN5:
		cyapa->ops = &cyapa_gen5_ops;
		break;
	case CYAPA_GEN3:
		cyapa->ops = &cyapa_gen3_ops;
		break;
	default:
		return -ENODEV;
	}

	error = cyapa->ops->operational_check(cyapa);
	if (!error && cyapa_is_operational_mode(cyapa))
		cyapa->operational = true;
	else
		cyapa->operational = false;

	return error;
}