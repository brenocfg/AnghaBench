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
struct seq_file {scalar_t__ private; } ;
struct docg3 {TYPE_1__* cascade; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_DEVICESELECT ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int device_id_show(struct seq_file *s, void *p)
{
	struct docg3 *docg3 = (struct docg3 *)s->private;
	int id;

	mutex_lock(&docg3->cascade->lock);
	id = doc_register_readb(docg3, DOC_DEVICESELECT);
	mutex_unlock(&docg3->cascade->lock);

	seq_printf(s, "DeviceId = %d\n", id);
	return 0;
}