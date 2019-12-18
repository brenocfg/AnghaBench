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
struct hvterm_priv {int /*<<< orphan*/  hvsi; int /*<<< orphan*/  termno; } ;
struct hvc_struct {size_t vtermno; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 int /*<<< orphan*/  hvsilib_write_mctrl (int /*<<< orphan*/ *,int) ; 
 struct hvterm_priv** hvterm_privs ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int hvterm_hvsi_tiocmset(struct hvc_struct *hp, unsigned int set,
				unsigned int clear)
{
	struct hvterm_priv *pv = hvterm_privs[hp->vtermno];

	pr_devel("HVSI@%x: Set modem control, set=%x,clr=%x\n",
		 pv->termno, set, clear);

	if (set & TIOCM_DTR)
		hvsilib_write_mctrl(&pv->hvsi, 1);
	else if (clear & TIOCM_DTR)
		hvsilib_write_mctrl(&pv->hvsi, 0);

	return 0;
}