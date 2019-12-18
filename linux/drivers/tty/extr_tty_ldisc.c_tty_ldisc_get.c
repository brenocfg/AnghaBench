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
struct tty_struct {int dummy; } ;
struct tty_ldisc_ops {int dummy; } ;
struct tty_ldisc {struct tty_struct* tty; struct tty_ldisc_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_MODULE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 struct tty_ldisc* ERR_CAST (struct tty_ldisc_ops*) ; 
 struct tty_ldisc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tty_ldisc_ops*) ; 
 int NR_LDISCS ; 
 int N_TTY ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct tty_ldisc_ops* get_ldops (int) ; 
 struct tty_ldisc* kmalloc (int,int) ; 
 int /*<<< orphan*/  request_module (char*,int) ; 
 int /*<<< orphan*/  tty_ldisc_autoload ; 

__attribute__((used)) static struct tty_ldisc *tty_ldisc_get(struct tty_struct *tty, int disc)
{
	struct tty_ldisc *ld;
	struct tty_ldisc_ops *ldops;

	if (disc < N_TTY || disc >= NR_LDISCS)
		return ERR_PTR(-EINVAL);

	/*
	 * Get the ldisc ops - we may need to request them to be loaded
	 * dynamically and try again.
	 */
	ldops = get_ldops(disc);
	if (IS_ERR(ldops)) {
		if (!capable(CAP_SYS_MODULE) && !tty_ldisc_autoload)
			return ERR_PTR(-EPERM);
		request_module("tty-ldisc-%d", disc);
		ldops = get_ldops(disc);
		if (IS_ERR(ldops))
			return ERR_CAST(ldops);
	}

	/*
	 * There is no way to handle allocation failure of only 16 bytes.
	 * Let's simplify error handling and save more memory.
	 */
	ld = kmalloc(sizeof(struct tty_ldisc), GFP_KERNEL | __GFP_NOFAIL);
	ld->ops = ldops;
	ld->tty = tty;

	return ld;
}