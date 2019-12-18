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
struct tty_struct {struct kgdb_nmi_tty_priv* driver_data; } ;
struct kgdb_nmi_tty_priv {int /*<<< orphan*/  port; } ;
struct file {unsigned int f_flags; } ;

/* Variables and functions */
 unsigned int O_ACCMODE ; 
 unsigned int O_RDONLY ; 
 unsigned int O_RDWR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_nmi_num_readers ; 
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int kgdb_nmi_tty_open(struct tty_struct *tty, struct file *file)
{
	struct kgdb_nmi_tty_priv *priv = tty->driver_data;
	unsigned int mode = file->f_flags & O_ACCMODE;
	int ret;

	ret = tty_port_open(&priv->port, tty, file);
	if (!ret && (mode == O_RDONLY || mode == O_RDWR))
		atomic_inc(&kgdb_nmi_num_readers);

	return ret;
}