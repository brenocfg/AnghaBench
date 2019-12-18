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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ fsp_activate_protocol (struct psmouse*) ; 
 scalar_t__ fsp_detect (struct psmouse*,int /*<<< orphan*/ ) ; 
 scalar_t__ fsp_get_version (struct psmouse*,int*) ; 

__attribute__((used)) static int fsp_reconnect(struct psmouse *psmouse)
{
	int version;

	if (fsp_detect(psmouse, 0))
		return -ENODEV;

	if (fsp_get_version(psmouse, &version))
		return -ENODEV;

	if (fsp_activate_protocol(psmouse))
		return -EIO;

	return 0;
}