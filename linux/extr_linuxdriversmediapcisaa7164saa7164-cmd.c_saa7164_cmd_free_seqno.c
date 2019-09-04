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
struct saa7164_dev {int /*<<< orphan*/  lock; TYPE_1__* cmds; } ;
struct TYPE_2__ {int inuse; size_t seqno; scalar_t__ timeout; scalar_t__ signalled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saa7164_cmd_free_seqno(struct saa7164_dev *dev, u8 seqno)
{
	mutex_lock(&dev->lock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		dev->cmds[seqno].inuse = 0;
		dev->cmds[seqno].signalled = 0;
		dev->cmds[seqno].timeout = 0;
	}
	mutex_unlock(&dev->lock);
}