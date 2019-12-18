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
struct firedtv {int /*<<< orphan*/  cadev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_device (int /*<<< orphan*/ ) ; 

void fdtv_ca_release(struct firedtv *fdtv)
{
	dvb_unregister_device(fdtv->cadev);
}