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
 int /*<<< orphan*/  DOC_ASICMODE ; 
 int DOC_ASICMODE_BDETCT_RESET ; 
 int DOC_ASICMODE_MDWREN ; 
#define  DOC_ASICMODE_NORMAL 130 
#define  DOC_ASICMODE_POWERDOWN 129 
 int DOC_ASICMODE_RAM_WE ; 
#define  DOC_ASICMODE_RESET 128 
 int DOC_ASICMODE_RSTIN_RESET ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int asic_mode_show(struct seq_file *s, void *p)
{
	struct docg3 *docg3 = (struct docg3 *)s->private;

	int pctrl, mode;

	mutex_lock(&docg3->cascade->lock);
	pctrl = doc_register_readb(docg3, DOC_ASICMODE);
	mode = pctrl & 0x03;
	mutex_unlock(&docg3->cascade->lock);

	seq_printf(s,
		   "%04x : RAM_WE=%d,RSTIN_RESET=%d,BDETCT_RESET=%d,WRITE_ENABLE=%d,POWERDOWN=%d,MODE=%d%d (",
		   pctrl,
		   pctrl & DOC_ASICMODE_RAM_WE ? 1 : 0,
		   pctrl & DOC_ASICMODE_RSTIN_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_BDETCT_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_MDWREN ? 1 : 0,
		   pctrl & DOC_ASICMODE_POWERDOWN ? 1 : 0,
		   mode >> 1, mode & 0x1);

	switch (mode) {
	case DOC_ASICMODE_RESET:
		seq_puts(s, "reset");
		break;
	case DOC_ASICMODE_NORMAL:
		seq_puts(s, "normal");
		break;
	case DOC_ASICMODE_POWERDOWN:
		seq_puts(s, "powerdown");
		break;
	}
	seq_puts(s, ")\n");
	return 0;
}