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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum msg_index_t { ____Placeholder_msg_index_t } msg_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSG_FIRST_INDEX ; 
 int MSG_FORMATTED_END ; 
 int MSG_FORMATTED_START ; 
 int MSG_LAST_INDEX ; 
 int /*<<< orphan*/  fmt_validate (char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char** speakup_default_msgs ; 
 TYPE_1__ speakup_info ; 
 char** speakup_msgs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

ssize_t spk_msg_set(enum msg_index_t index, char *text, size_t length)
{
	char *newstr = NULL;
	unsigned long flags;

	if ((index < MSG_FIRST_INDEX) || (index >= MSG_LAST_INDEX))
		return -EINVAL;

	newstr = kmalloc(length + 1, GFP_KERNEL);
	if (!newstr)
		return -ENOMEM;

	memcpy(newstr, text, length);
	newstr[length] = '\0';
	if (index >= MSG_FORMATTED_START &&
	    index <= MSG_FORMATTED_END &&
	    !fmt_validate(speakup_default_msgs[index], newstr)) {
		kfree(newstr);
		return -EINVAL;
	}
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	if (speakup_msgs[index] != speakup_default_msgs[index])
		kfree(speakup_msgs[index]);
	speakup_msgs[index] = newstr;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return 0;
}