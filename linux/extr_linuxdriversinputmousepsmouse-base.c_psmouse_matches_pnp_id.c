#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serio {int /*<<< orphan*/ * firmware_id; } ;
struct TYPE_2__ {struct serio* serio; } ;
struct psmouse {TYPE_1__ ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_check_pnp_id (char*,char const* const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 char* strsep (char**,char*) ; 

bool psmouse_matches_pnp_id(struct psmouse *psmouse, const char * const ids[])
{
	struct serio *serio = psmouse->ps2dev.serio;
	char *p, *fw_id_copy, *save_ptr;
	bool found = false;

	if (strncmp(serio->firmware_id, "PNP: ", 5))
		return false;

	fw_id_copy = kstrndup(&serio->firmware_id[5],
			      sizeof(serio->firmware_id) - 5,
			      GFP_KERNEL);
	if (!fw_id_copy)
		return false;

	save_ptr = fw_id_copy;
	while ((p = strsep(&fw_id_copy, " ")) != NULL) {
		if (psmouse_check_pnp_id(p, ids)) {
			found = true;
			break;
		}
	}

	kfree(save_ptr);
	return found;
}