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
struct uea_softc {scalar_t__ cmv_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  uea_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int uea_wait (struct uea_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wait_cmv_ack(struct uea_softc *sc)
{
	int ret = uea_wait(sc, sc->cmv_ack , ACK_TIMEOUT);

	sc->cmv_ack = 0;

	uea_dbg(INS_TO_USBDEV(sc), "wait_event_timeout : %d ms\n",
			jiffies_to_msecs(ret));

	if (ret < 0)
		return ret;

	return (ret == 0) ? -ETIMEDOUT : 0;
}