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
struct psmouse_protocol {int dummy; } ;
typedef  enum psmouse_type { ____Placeholder_psmouse_type } psmouse_type ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct psmouse_protocol* __psmouse_protocol_by_type (int) ; 
 struct psmouse_protocol const* psmouse_protocols ; 

__attribute__((used)) static const struct psmouse_protocol *psmouse_protocol_by_type(enum psmouse_type type)
{
	const struct psmouse_protocol *proto;

	proto = __psmouse_protocol_by_type(type);
	if (proto)
		return proto;

	WARN_ON(1);
	return &psmouse_protocols[0];
}