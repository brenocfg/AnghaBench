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
struct vc_data {size_t vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/ * font_backup; scalar_t__* havethisconsole; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** mysisusbs ; 
 int /*<<< orphan*/  sisusb_delete ; 
 struct sisusb_usb_data* sisusb_get_sisusb (size_t) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sisusbcon_deinit(struct vc_data *c)
{
	struct sisusb_usb_data *sisusb;
	int i;

	/* This is called by do_take_over_console()
	 * and others, ie not under our control.
	 */

	sisusb = sisusb_get_sisusb(c->vc_num);
	if (!sisusb)
		return;

	mutex_lock(&sisusb->lock);

	/* Clear ourselves in mysisusbs */
	mysisusbs[c->vc_num] = NULL;

	sisusb->havethisconsole[c->vc_num] = 0;

	/* Free our font buffer if all consoles are gone */
	if (sisusb->font_backup) {
		for(i = 0; i < MAX_NR_CONSOLES; i++) {
			if (sisusb->havethisconsole[c->vc_num])
				break;
		}
		if (i == MAX_NR_CONSOLES) {
			vfree(sisusb->font_backup);
			sisusb->font_backup = NULL;
		}
	}

	mutex_unlock(&sisusb->lock);

	/* decrement the usage count on our sisusb */
	kref_put(&sisusb->kref, sisusb_delete);
}