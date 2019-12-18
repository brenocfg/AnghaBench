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
struct rtllib_device {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  global_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_COUNTRY_IE_VALID (struct rtllib_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct rtllib_device*) ; 
 scalar_t__ RTLLIB_NOLINK ; 
 int /*<<< orphan*/  rtllib_softmac_check_all_nets (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_start_scan (struct rtllib_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtllib_start_bss(struct rtllib_device *ieee)
{
	unsigned long flags;

	if (IS_DOT11D_ENABLE(ieee) && !IS_COUNTRY_IE_VALID(ieee)) {
		if (!ieee->global_domain)
			return;
	}
	/* check if we have already found the net we
	 * are interested in (if any).
	 * if not (we are disassociated and we are not
	 * in associating / authenticating phase) start the background scanning.
	 */
	rtllib_softmac_check_all_nets(ieee);

	/* ensure no-one start an associating process (thus setting
	 * the ieee->state to rtllib_ASSOCIATING) while we
	 * have just checked it and we are going to enable scan.
	 * The rtllib_new_net function is always called with
	 * lock held (from both rtllib_softmac_check_all_nets and
	 * the rx path), so we cannot be in the middle of such function
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->state == RTLLIB_NOLINK)
		rtllib_start_scan(ieee);
	spin_unlock_irqrestore(&ieee->lock, flags);
}