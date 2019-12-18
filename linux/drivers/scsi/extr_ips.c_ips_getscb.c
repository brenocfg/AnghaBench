#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* q_next; scalar_t__ flags; } ;
typedef  TYPE_1__ ips_scb_t ;
struct TYPE_8__ {TYPE_1__* scb_freelist; } ;
typedef  TYPE_2__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static ips_scb_t *
ips_getscb(ips_ha_t * ha)
{
	ips_scb_t *scb;

	METHOD_TRACE("ips_getscb", 1);

	if ((scb = ha->scb_freelist) == NULL) {

		return (NULL);
	}

	ha->scb_freelist = scb->q_next;
	scb->flags = 0;
	scb->q_next = NULL;

	ips_init_scb(ha, scb);

	return (scb);
}