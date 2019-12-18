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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {struct pti_tty* driver_data; } ;
struct pti_tty {int /*<<< orphan*/ * mc; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  pti_write_to_aperture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pti_tty_driver_write(struct tty_struct *tty,
	const unsigned char *buf, int len)
{
	struct pti_tty *pti_tty_data = tty->driver_data;
	if ((pti_tty_data != NULL) && (pti_tty_data->mc != NULL)) {
		pti_write_to_aperture(pti_tty_data->mc, (u8 *)buf, len);
		return len;
	}
	/*
	 * we can't write to the pti hardware if the private driver_data
	 * and the mc address is not there.
	 */
	else
		return -EFAULT;
}