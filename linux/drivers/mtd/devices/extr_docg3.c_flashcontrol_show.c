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
typedef  int u8 ;
struct seq_file {scalar_t__ private; } ;
struct docg3 {TYPE_1__* cascade; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DOC_CTRL_CE ; 
 int DOC_CTRL_FLASHREADY ; 
 int DOC_CTRL_PROTECTION_ERROR ; 
 int DOC_CTRL_SEQUENCE_ERROR ; 
 int DOC_CTRL_VIOLATION ; 
 int /*<<< orphan*/  DOC_FLASHCONTROL ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static int flashcontrol_show(struct seq_file *s, void *p)
{
	struct docg3 *docg3 = (struct docg3 *)s->private;

	u8 fctrl;

	mutex_lock(&docg3->cascade->lock);
	fctrl = doc_register_readb(docg3, DOC_FLASHCONTROL);
	mutex_unlock(&docg3->cascade->lock);

	seq_printf(s, "FlashControl : 0x%02x (%s,CE# %s,%s,%s,flash %s)\n",
		   fctrl,
		   fctrl & DOC_CTRL_VIOLATION ? "protocol violation" : "-",
		   fctrl & DOC_CTRL_CE ? "active" : "inactive",
		   fctrl & DOC_CTRL_PROTECTION_ERROR ? "protection error" : "-",
		   fctrl & DOC_CTRL_SEQUENCE_ERROR ? "sequence error" : "-",
		   fctrl & DOC_CTRL_FLASHREADY ? "ready" : "not ready");

	return 0;
}