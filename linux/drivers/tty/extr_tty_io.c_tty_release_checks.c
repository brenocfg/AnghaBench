__attribute__((used)) static int tty_release_checks(struct tty_struct *tty, int idx)
{
#ifdef TTY_PARANOIA_CHECK
	if (idx < 0 || idx >= tty->driver->num) {
		tty_debug(tty, "bad idx %d\n", idx);
		return -1;
	}

	/* not much to check for devpts */
	if (tty->driver->flags & TTY_DRIVER_DEVPTS_MEM)
		return 0;

	if (tty != tty->driver->ttys[idx]) {
		tty_debug(tty, "bad driver table[%d] = %p\n",
			  idx, tty->driver->ttys[idx]);
		return -1;
	}
	if (tty->driver->other) {
		struct tty_struct *o_tty = tty->link;

		if (o_tty != tty->driver->other->ttys[idx]) {
			tty_debug(tty, "bad other table[%d] = %p\n",
				  idx, tty->driver->other->ttys[idx]);
			return -1;
		}
		if (o_tty->link != tty) {
			tty_debug(tty, "bad link = %p\n", o_tty->link);
			return -1;
		}
	}
#endif
	return 0;
}