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
struct tty_struct {int index; struct pti_tty* driver_data; } ;
struct tty_driver {int dummy; } ;
struct pti_tty {int /*<<< orphan*/ * mc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTITTY_MINOR_START ; 
 int /*<<< orphan*/  kfree (struct pti_tty*) ; 
 struct pti_tty* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* pti_request_masterchannel (int,int /*<<< orphan*/ *) ; 
 int tty_standard_install (struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int pti_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	int idx = tty->index;
	struct pti_tty *pti_tty_data;
	int ret = tty_standard_install(driver, tty);

	if (ret == 0) {
		pti_tty_data = kmalloc(sizeof(struct pti_tty), GFP_KERNEL);
		if (pti_tty_data == NULL)
			return -ENOMEM;

		if (idx == PTITTY_MINOR_START)
			pti_tty_data->mc = pti_request_masterchannel(0, NULL);
		else
			pti_tty_data->mc = pti_request_masterchannel(2, NULL);

		if (pti_tty_data->mc == NULL) {
			kfree(pti_tty_data);
			return -ENXIO;
		}
		tty->driver_data = pti_tty_data;
	}

	return ret;
}