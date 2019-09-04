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
struct psmouse_protocol {scalar_t__ (* init ) (struct psmouse*) ;int /*<<< orphan*/  try_passthru; int /*<<< orphan*/  detect; } ;
struct psmouse {int dummy; } ;
typedef  enum psmouse_type { ____Placeholder_psmouse_type } psmouse_type ;

/* Variables and functions */
 unsigned int PSMOUSE_IMEX ; 
 struct psmouse_protocol* __psmouse_protocol_by_type (int) ; 
 int /*<<< orphan*/  psmouse_do_detect (int /*<<< orphan*/ ,struct psmouse*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct psmouse*) ; 

__attribute__((used)) static bool psmouse_try_protocol(struct psmouse *psmouse,
				 enum psmouse_type type,
				 unsigned int *max_proto,
				 bool set_properties, bool init_allowed)
{
	const struct psmouse_protocol *proto;

	proto = __psmouse_protocol_by_type(type);
	if (!proto)
		return false;

	if (!psmouse_do_detect(proto->detect, psmouse, proto->try_passthru,
			       set_properties))
		return false;

	if (set_properties && proto->init && init_allowed) {
		if (proto->init(psmouse) != 0) {
			/*
			 * We detected device, but init failed. Adjust
			 * max_proto so we only try standard protocols.
			 */
			if (*max_proto > PSMOUSE_IMEX)
				*max_proto = PSMOUSE_IMEX;

			return false;
		}
	}

	return true;
}