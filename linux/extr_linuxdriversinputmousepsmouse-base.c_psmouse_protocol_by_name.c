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
struct psmouse_protocol {int /*<<< orphan*/  alias; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct psmouse_protocol const*) ; 
 struct psmouse_protocol const* psmouse_protocols ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static const struct psmouse_protocol *psmouse_protocol_by_name(const char *name, size_t len)
{
	const struct psmouse_protocol *p;
	int i;

	for (i = 0; i < ARRAY_SIZE(psmouse_protocols); i++) {
		p = &psmouse_protocols[i];

		if ((strlen(p->name) == len && !strncmp(p->name, name, len)) ||
		    (strlen(p->alias) == len && !strncmp(p->alias, name, len)))
			return &psmouse_protocols[i];
	}

	return NULL;
}