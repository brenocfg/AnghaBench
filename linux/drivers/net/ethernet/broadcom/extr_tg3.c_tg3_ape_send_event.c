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
typedef  int u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 int APE_EVENT_1 ; 
 int APE_EVENT_STATUS_EVENT_PENDING ; 
 int APE_FW_STATUS_READY ; 
 int APE_SEG_SIG_MAGIC ; 
 int EAGAIN ; 
 int /*<<< orphan*/  TG3_APE_EVENT ; 
 int /*<<< orphan*/  TG3_APE_EVENT_STATUS ; 
 int /*<<< orphan*/  TG3_APE_FW_STATUS ; 
 int /*<<< orphan*/  TG3_APE_LOCK_MEM ; 
 int /*<<< orphan*/  TG3_APE_SEG_SIG ; 
 int tg3_ape_event_lock (struct tg3*,int) ; 
 int tg3_ape_read32 (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_unlock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_ape_send_event(struct tg3 *tp, u32 event)
{
	int err;
	u32 apedata;

	apedata = tg3_ape_read32(tp, TG3_APE_SEG_SIG);
	if (apedata != APE_SEG_SIG_MAGIC)
		return -EAGAIN;

	apedata = tg3_ape_read32(tp, TG3_APE_FW_STATUS);
	if (!(apedata & APE_FW_STATUS_READY))
		return -EAGAIN;

	/* Wait for up to 20 millisecond for APE to service previous event. */
	err = tg3_ape_event_lock(tp, 20000);
	if (err)
		return err;

	tg3_ape_write32(tp, TG3_APE_EVENT_STATUS,
			event | APE_EVENT_STATUS_EVENT_PENDING);

	tg3_ape_unlock(tp, TG3_APE_LOCK_MEM);
	tg3_ape_write32(tp, TG3_APE_EVENT, APE_EVENT_1);

	return 0;
}