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
struct smb347_charger {int /*<<< orphan*/  lock; scalar_t__ mains_online; scalar_t__ usb_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool smb347_is_ps_online(struct smb347_charger *smb)
{
	bool ret;

	mutex_lock(&smb->lock);
	ret = smb->usb_online || smb->mains_online;
	mutex_unlock(&smb->lock);

	return ret;
}