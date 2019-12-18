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
struct uea_softc {int (* stat ) (struct uea_softc*) ;scalar_t__ reset; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int stub1 (struct uea_softc*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int uea_start_reset (struct uea_softc*) ; 
 int /*<<< orphan*/  uea_wait (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_kthread(void *data)
{
	struct uea_softc *sc = data;
	int ret = -EAGAIN;

	set_freezable();
	uea_enters(INS_TO_USBDEV(sc));
	while (!kthread_should_stop()) {
		if (ret < 0 || sc->reset)
			ret = uea_start_reset(sc);
		if (!ret)
			ret = sc->stat(sc);
		if (ret != -EAGAIN)
			uea_wait(sc, 0, msecs_to_jiffies(1000));
		try_to_freeze();
	}
	uea_leaves(INS_TO_USBDEV(sc));
	return ret;
}