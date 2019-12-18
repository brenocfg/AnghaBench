#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum ibmvfc_ae_link_state { ____Placeholder_ibmvfc_ae_link_state } ibmvfc_ae_link_state ;
struct TYPE_3__ {int state; char const* desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* link_desc ; 

__attribute__((used)) static const char *ibmvfc_get_link_state(enum ibmvfc_ae_link_state state)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(link_desc); i++)
		if (link_desc[i].state == state)
			return link_desc[i].desc;

	return "";
}