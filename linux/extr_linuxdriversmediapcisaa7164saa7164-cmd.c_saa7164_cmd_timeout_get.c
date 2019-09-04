#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct saa7164_dev {int /*<<< orphan*/  lock; TYPE_1__* cmds; } ;
struct TYPE_2__ {int inuse; size_t seqno; int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 saa7164_cmd_timeout_get(struct saa7164_dev *dev, u8 seqno)
{
	int ret = 0;

	mutex_lock(&dev->lock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		ret = dev->cmds[seqno].timeout;
	}
	mutex_unlock(&dev->lock);

	return ret;
}