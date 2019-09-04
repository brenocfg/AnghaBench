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
struct ide_cmd {int dummy; } ;

/* Variables and functions */

void ide_tf_dump(const char *s, struct ide_cmd *cmd)
{
#ifdef DEBUG
	printk("%s: tf: feat 0x%02x nsect 0x%02x lbal 0x%02x "
		"lbam 0x%02x lbah 0x%02x dev 0x%02x cmd 0x%02x\n",
	       s, cmd->tf.feature, cmd->tf.nsect,
	       cmd->tf.lbal, cmd->tf.lbam, cmd->tf.lbah,
	       cmd->tf.device, cmd->tf.command);
	printk("%s: hob: nsect 0x%02x lbal 0x%02x lbam 0x%02x lbah 0x%02x\n",
	       s, cmd->hob.nsect, cmd->hob.lbal, cmd->hob.lbam, cmd->hob.lbah);
#endif
}