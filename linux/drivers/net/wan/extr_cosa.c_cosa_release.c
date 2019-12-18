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
struct inode {int dummy; } ;
struct file {struct channel_data* private_data; } ;
struct cosa_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;
struct channel_data {int /*<<< orphan*/  usage; struct cosa_data* cosa; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cosa_release(struct inode *inode, struct file *file)
{
	struct channel_data *channel = file->private_data;
	struct cosa_data *cosa;
	unsigned long flags;

	cosa = channel->cosa;
	spin_lock_irqsave(&cosa->lock, flags);
	cosa->usage--;
	channel->usage--;
	spin_unlock_irqrestore(&cosa->lock, flags);
	return 0;
}