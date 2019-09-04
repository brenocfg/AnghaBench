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
 int /*<<< orphan*/  fsp_onpad_hscr (struct psmouse*,int) ; 
 int /*<<< orphan*/  fsp_onpad_vscr (struct psmouse*,int) ; 
 int /*<<< orphan*/  fsp_opc_tag_enable (struct psmouse*,int) ; 

__attribute__((used)) static void fsp_reset(struct psmouse *psmouse)
{
	fsp_opc_tag_enable(psmouse, false);
	fsp_onpad_vscr(psmouse, false);
	fsp_onpad_hscr(psmouse, false);
}