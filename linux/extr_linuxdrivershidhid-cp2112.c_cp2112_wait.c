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
struct cp2112_device {int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp2112_wait(struct cp2112_device *dev, atomic_t *avail)
{
	int ret = 0;

	/* We have sent either a CP2112_TRANSFER_STATUS_REQUEST or a
	 * CP2112_DATA_READ_FORCE_SEND and we are waiting for the response to
	 * come in cp2112_raw_event or timeout. There will only be one of these
	 * in flight at any one time. The timeout is extremely large and is a
	 * last resort if the CP2112 has died. If we do timeout we don't expect
	 * to receive the response which would cause data races, it's not like
	 * we can do anything about it anyway.
	 */
	ret = wait_event_interruptible_timeout(dev->wait,
		atomic_read(avail), msecs_to_jiffies(RESPONSE_TIMEOUT));
	if (-ERESTARTSYS == ret)
		return ret;
	if (!ret)
		return -ETIMEDOUT;

	atomic_set(avail, 0);
	return 0;
}