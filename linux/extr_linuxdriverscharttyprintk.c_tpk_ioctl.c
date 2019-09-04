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
struct ttyprintk_port {int dummy; } ;
struct tty_struct {struct ttyprintk_port* driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int EOPNOTSUPP ; 
#define  TIOCCONS 128 

__attribute__((used)) static int tpk_ioctl(struct tty_struct *tty,
			unsigned int cmd, unsigned long arg)
{
	struct ttyprintk_port *tpkp = tty->driver_data;

	if (!tpkp)
		return -EINVAL;

	switch (cmd) {
	/* Stop TIOCCONS */
	case TIOCCONS:
		return -EOPNOTSUPP;
	default:
		return -ENOIOCTLCMD;
	}
	return 0;
}