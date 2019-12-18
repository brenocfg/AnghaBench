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
 int hvsilib_open (int /*<<< orphan*/ *,struct hvc_struct*) ; 
 struct hvterm_priv** hvterm_privs ; 
 int notifier_add_irq (struct hvc_struct*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hvterm_hvsi_open(struct hvc_struct *hp, int data)
{
	struct hvterm_priv *pv = hvterm_privs[hp->vtermno];
	int rc;

	pr_devel("HVSI@%x: open !\n", pv->termno);

	rc = notifier_add_irq(hp, data);
	if (rc)
		return rc;

	return hvsilib_open(&pv->hvsi, hp);
}